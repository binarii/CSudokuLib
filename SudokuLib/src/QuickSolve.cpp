#include "QuickSolve.h"
#include "SudokuBoard.h"

namespace sudoku
{
	template <int boxSize>
	QuickSolve<boxSize>::QuickSolve()
	{
		m_maxSolutions = 1;
		m_solveTime = 0.0;
	}

	template <int boxSize>
	QuickSolve<boxSize>::~QuickSolve()
	{

	}

	template <int boxSize>
	int QuickSolve<boxSize>::Solve(Board<boxSize>& board)
	{
		m_timer.StartTimer();
		int solutionCount = BacktrackSolve(board);
		m_solveTime = m_timer.GetTime();

		return solutionCount;
	}
	
	template <int boxSize>
	double QuickSolve<boxSize>::GetSolveTime()
	{
		return m_solveTime;
	}

	template <int boxSize>
	int QuickSolve<boxSize>::BacktrackSolve(Board<boxSize>& board)
	{
		if(board.GetSetCount() == GRID) return 1;

		BITMASK val = 0;
		CELL_INDEX pos = INT_MAX;
		int solutionsFound = 0;
		int count = FindSingles(board, pos, val);

		if(count == 0) return 0;

		for(int i = (val & -val); val; i = (val & -val))
		{
			board.SetCell(pos, i);
			solutionsFound += BacktrackSolve(board);
			if(solutionsFound >= m_maxSolutions)
				return solutionsFound;
			board.ClearCell(pos);
			val &= ~i;
		}

		return solutionsFound;
	}

	template <int boxSize>
	int QuickSolve<boxSize>::FindSingles(Board<boxSize>& board, CELL_INDEX& pos, BITMASK& value)
	{
		int count;
		int savePos = -1;
		int saveCount = UNIT + 1;
		int i, j, x;

		BITMASK saveVal = 0;

		for(i = 0; i < GRID; ++i)
		{
			if(board.GetCellMask(i) != 0)
			{
				board.IgnoreCellPossible(i);
				continue;
			}

			// Update and get possibilities for cell i
			board.UpdateCellPossible(i);
			BITMASK possible = board.GetCellPossible(i);

			// Get the bit count for the cell
			count = BITCOUNT(possible);
			
			// If cell is open and it has no possibilities, illegal board
			if(count == 0)
			{
				return 0;
			}
			// If cell has one possibility play it
			else if(count == 1)
			{
				pos = i;
				value = possible;
				return 1;
			}
			// Else continue to try and find lowest count on a cell
			else if(count < saveCount)
			{
				savePos = i;
				saveVal = possible;
				saveCount = count;
			}
		}


		for(i = 0; i < UNIT*3; ++i)
		{
			BITMASK once = 0;
			BITMASK twice = 0;
			BITMASK all = 0;

			for(j = 0; j < UNIT; ++j)
			{
				// Get the board position
				x = board.IterateGroups(i, j);

				// Get possible mask and value mask
				BITMASK possible = board.GetCellPossible(x);
				BITMASK boardVal = board.GetCellMask(x);

				all |= (possible | boardVal);
				twice |= (once & possible);
				once |= possible;
			}

			if(all != MASK) // hidden zero, board is illegal
				return 0;

			once &= ~twice;

			if(!once) // If none are seen only once, continue
				continue;
			
			// Find the hidden single
			once &= -once; // Get least set bit
			for(j = 0; j < UNIT; ++j)
			{
				pos = board.IterateGroups(i, j);
				if(board.GetCellPossible(pos) & once)
				{
					value = once;
					return 1;
				}
			}
			
		}

		pos = savePos;
		value = saveVal;
		return (saveCount > UNIT) ? 0 : saveCount;
	}

	template class QuickSolve<2>;
	template class QuickSolve<3>;
	template class QuickSolve<4>;
	template class QuickSolve<5>;

}