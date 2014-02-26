#ifndef _MINIMIZEBOARD_H_
#define _MINIMIZEBOARD_H_

#include "Types.h"
#include "Timer.h"

namespace sudoku
{
	// Forward the board class
	template <int boxSize>
	class Board;

	template <int boxSize>
	class QuickSolve;

	template <int boxSize>
	class MinimizeBoard
	{
	public:
		MinimizeBoard();
		~MinimizeBoard();

		void Minimize(Board<boxSize>& board);

		double GetSolveTime();

	private:
		void MinimizeNone(Board<boxSize>& board);
		void MinimizeHoriz(Board<boxSize>& board);
		void MinimizeVert(Board<boxSize>& board);
		void MinimizeDiag(Board<boxSize>& board);

		void MinimizePattern(Board<boxSize>& board, CELL_INDEX* digArray, int n, int rate);

	private:
		double m_solveTime;
		Timer m_timer;

		QuickSolve<boxSize> m_solver;
	};
}

#endif