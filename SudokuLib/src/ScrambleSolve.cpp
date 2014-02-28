#include "ScrambleSolve.h"
#include "SudokuBoard.h"
#include "Util.h"

// Defines for constants (based on template)
#define BOX  (boxSize)          // Box side length
#define UNIT (BOX * BOX)        // Unit side length (row, col)
#define GRID (UNIT * UNIT)      // Grid size (typical is 81)
#define MASK ((1<<(UNIT+1))-2)  // Mask for all bits except 0

namespace sudoku
{	
	template <int boxSize>
	ScrambleSolve<boxSize>::ScrambleSolve()
	{
		m_solveTime = 0.0;
	}

	template <int boxSize>
	ScrambleSolve<boxSize>::~ScrambleSolve()
	{

	}

	template <int boxSize>
	int ScrambleSolve<boxSize>::solve(Board<boxSize>& board)
	{
		m_timer.StartTimer();
		int solutionCount = BacktrackSolve(board);
		m_solveTime = m_timer.GetTime();

		return solutionCount;
	}

	template <int boxSize>
	double ScrambleSolve<boxSize>::GetSolveTime()
	{
		return m_solveTime;
	}

	template <int boxSize>
	int ScrambleSolve<boxSize>::BacktrackSolve(Board<boxSize>& board)
	{
		if(board.GetSetCount() == GRID)
			return 1;

		int solutionsFound = 0;
		CELL_INDEX pos = board.GetSetCount();

		// Get the possible values for the cell
		board.UpdateCellPossible(pos);
		BITMASK possible = board.GetCellPossible(pos);

		// Choose the order to try values
		BITMASK cellOrder[UNIT];
		for(int i = 0; i < UNIT; i++)
			cellOrder[i] = (1 << (i + 1));
		util::ArrayShuffle<BITMASK>(cellOrder, UNIT);

		// Go through values and recursively try them
		for(int i = 0; i < UNIT; i++)
		{
			if(cellOrder[i] & possible)
			{
				board.SetCell(pos, cellOrder[i]);
				solutionsFound = BacktrackSolve(board);
				if(solutionsFound > 0)
					return solutionsFound;
				board.ClearCell(pos);

				possible &= ~cellOrder[i];
			}
		}

		return 0;
	}

	template class ScrambleSolve<2>;
	template class ScrambleSolve<3>;
	template class ScrambleSolve<4>;
	template class ScrambleSolve<5>;
}