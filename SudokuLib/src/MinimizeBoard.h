#ifndef _MINIMIZEBOARD_H_
#define _MINIMIZEBOARD_H_

#include "SudokuPrerequisites.h"
#include "Timer.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
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

		void Minimize(BoardAbstract<size>& board, MinimizeType type);

		double GetSolveTime();

	private:
		void MinimizeNone(BoardAbstract<size>& board);
		void MinimizeHoriz(BoardAbstract<size>& board);
		void MinimizeVert(BoardAbstract<size>& board);
		void MinimizeDiag(BoardAbstract<size>& board);

		void MinimizePattern(BoardAbstract<size>& board, CELL_INDEX* digArray, int n, int rate);

	private:
		double m_solveTime;
		Timer m_timer;
	};
}

#endif