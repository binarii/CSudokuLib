#ifndef _MINIMIZEBOARD_H_
#define _MINIMIZEBOARD_H_

#include "Types.h"
#include "Timer.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;

	template <int size>
	class QuickSolve;

	enum MinimizeType
	{
		MT_NONE,
		MT_HORIZONTAL,
		MT_VERTICAL,
		MT_DIAGONAL
	};

	template <int size>
	class MinimizeBoard : PuzzleDimensions<size>
	{
	public:
		MinimizeBoard();
		~MinimizeBoard();

		void Minimize(Board<size>& board, MinimizeType type);

		double GetSolveTime();

	private:
		void MinimizeNone(Board<size>& board);
		void MinimizeHoriz(Board<size>& board);
		void MinimizeVert(Board<size>& board);
		void MinimizeDiag(Board<size>& board);

		void MinimizePattern(Board<size>& board, CELL_INDEX* digArray, int n, int rate);

	private:
		double m_solveTime;
		Timer m_timer;
	};
}

#endif