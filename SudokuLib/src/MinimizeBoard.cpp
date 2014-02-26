#include "MinimizeBoard.h"
#include "SudokuBoard.h"
#include "QuickSolve.h"
#include "Util.h"

namespace sudoku
{
	template <int boxSize>
	MinimizeBoard<boxSize>::MinimizeBoard()
	{
		m_solveTime = 0.0;
		m_solver.SetMaxSolutionCount(2);
	}

	template <int boxSize>
	MinimizeBoard<boxSize>::~MinimizeBoard()
	{

	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::Minimize(Board<boxSize>& board)
	{
		m_timer.StartTimer();

		MinimizeNone(board);

		m_solveTime = m_timer.GetTime();
	}

	template <int boxSize>
	double MinimizeBoard<boxSize>::GetSolveTime()
	{
		return m_solveTime;
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeNone(Board<boxSize>& board)
	{
		CELL_INDEX digArray[GRID];
		for(int i = 0; i < GRID; i++) digArray[i] = i;
		util::ArrayShuffle<CELL_INDEX>(digArray, GRID);

		MinimizePattern(board, digArray, GRID, 1);
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeHoriz(Board<boxSize>& board)
	{

	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeVert(Board<boxSize>& board)
	{

	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeDiag(Board<boxSize>& board)
	{

	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizePattern
		(Board<boxSize>& board, CELL_INDEX* digArray, int n, int rate)
	{
		int solutionCount;
		Board<boxSize> boardCpy(board);

		for(int i = 0; i < n; i++)
		{
			// Make a copy of the board and dig cells
			boardCpy.Copy(board);
			for(int j = 0; j < rate; j++)
				boardCpy.ClearCell(digArray[i + j]);

			// Check if it is still unique
			solutionCount = m_solver.Solve(boardCpy);

			// If it is unique we can dig these cells
			if(solutionCount == 1)
				for(int j = 0; j < rate; j++)
					board.ClearCell(digArray[i + j]);
		}
	}

	template class MinimizeBoard<2>;
	template class MinimizeBoard<3>;
	template class MinimizeBoard<4>;
	template class MinimizeBoard<5>;
}