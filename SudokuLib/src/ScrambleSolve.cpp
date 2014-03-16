#include "ScrambleSolve.h"
#include "Board.h"
#include "Util.h"

namespace sudoku
{	
	template <int size>
	ScrambleSolve<size>::ScrambleSolve()
	{
		m_solveTime = 0.0;
	}

	template <int size>
	ScrambleSolve<size>::~ScrambleSolve()
	{

	}

	template <int size>
	int ScrambleSolve<size>::solve(Board<size>& board)
	{
		m_timer.StartTimer();
		int solutionCount = BacktrackSolve(board);
		m_solveTime = m_timer.GetTime();

		return solutionCount;
	}

	template <int size>
	double ScrambleSolve<size>::GetSolveTime()
	{
		return m_solveTime;
	}

	template <int size>
	int ScrambleSolve<size>::BacktrackSolve(Board<size>& board)
	{
		if(board.BoardFull())
			return 1;

		int solutionsFound = 0;
		CELL_INDEX pos = board.GetFilledCount();

		// Get the possible values for the cell
		board.UpdateCandidates(pos);
		BITMASK possible = board.GetCandidates(pos);

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
				board.Set(pos, cellOrder[i]);
				solutionsFound = BacktrackSolve(board);
				if(solutionsFound > 0)
					return solutionsFound;
				board.Remove(pos);

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