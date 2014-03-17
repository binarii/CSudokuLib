#include "QuickSolve.h"

#include "Board.h"
#include "BitCount.h"

#include "Techniques\HiddenSingle.h"
#include "Techniques\NakedSingle.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((dim.BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	template <int size>
	QuickSolve<size>::QuickSolve()
	{
		m_maxSolutions = 1;
		m_solveTime = 0.0;
	}

	template <int size>
	QuickSolve<size>::~QuickSolve()
	{

	}

	template <>
	int QuickSolve<3>::Solve(Board<3>& board)
	{
		StartTimer();
		NakedSingle ns;
		HiddenSingle hs;
		int count = 1;

		while(count > 0 && !board.BoardFull() && m_maxSolutions == 1)
		{
			count = 0;
			count += ns.Step(board);
			count += hs.Step(board);
		}

		int solutionCount = BacktrackSolve(board);
		StopTimer();

		return solutionCount;
	}

	template <int size>
	int QuickSolve<size>::Solve(Board<size>& board)
	{
		StartTimer();
		int solutionCount = BacktrackSolve(board);
		StopTimer();

		return solutionCount;
	}
		
	template <int size>
	void QuickSolve<size>::SetMaxSolutionCount(int count)
	{
		m_maxSolutions = count;
	}

	template <int size>
	int QuickSolve<size>::BacktrackSolve(Board<size>& board)
	{
		if(board.BoardFull()) return 1;

		BITMASK val = 0;
		CELL_INDEX pos = INT_MAX;
		int solutionsFound = 0;
		int count = FindSingles(board, pos, val);

		if(count == 0) return 0;

		for(int i = (val & -val); val; i = (val & -val))
		{
			board.Set(pos, i);
			solutionsFound += BacktrackSolve(board);
			if(solutionsFound >= m_maxSolutions)
				return solutionsFound;
			board.Remove(pos);
			val &= ~i;
		}

		return solutionsFound;
	}

	template <int size>
	int QuickSolve<size>::FindSingles(Board<size>& board, CELL_INDEX& pos, BITMASK& value)
	{
		int count;
		int savePos = -1;
		int saveCount = dim.UNIT + 1;
		int i, j, x;

		BITMASK saveVal = 0;

		for(i = 0; i < dim.GRID; ++i)
		{
			// Update and get possibilities for cell i
			board.UpdateCandidates(i);
			
			if(board.GetValue(i) != 0)
				continue;

			BITMASK possible = board.GetCandidates(i);

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


		for(i = 0; i < dim.UNIT*3; ++i)
		{
			BITMASK once = 0;
			BITMASK twice = 0;
			BITMASK all = 0;

			for(j = 0; j < dim.UNIT; ++j)
			{
				// Get the board position
				x = board.Iterate(i, j);

				// Get possible mask and value mask
				BITMASK possible = board.GetCandidates(x);
				BITMASK boardVal = board.GetValue(x);

				all |= (possible | boardVal);
				twice |= (once & possible);
				once |= possible;
			}

			if(all != dim.MASK) // hidden zero, board is illegal
				return 0;

			once &= ~twice;

			if(!once) // If none are seen only once, continue
				continue;
			
			// Find the hidden single
			once &= -once; // Get least set bit
			for(j = 0; j < dim.UNIT; ++j)
			{
				pos = board.Iterate(i, j);
				if(board.GetCandidates(pos) & once)
				{
					value = once;
					return 1;
				}
			}			
		}

		pos = savePos;
		value = saveVal;
		return (saveCount > dim.UNIT) ? 0 : saveCount;
	}

	template class QuickSolve<2>;
	template class QuickSolve<3>;
	template class QuickSolve<4>;
	template class QuickSolve<5>;
}