#ifndef _SOLVEMETHOD_H_
#define _SOLVEMETHOD_H_

#include "SudokuPrerequisites.h"
#include "PuzzleDimensions.h"
#include "Timer.h"

namespace sudoku
{
	template <int size>
	class SolveMethod {
	public:
		virtual int solve(BoardAbstract<size>& board) = 0;

		void startTimer() { m_timer.StartTimer(); }
		void stopTimer()  { m_solveTime = m_timer.GetTime(); }
		double getTime()  { return m_solveTime; }

	protected:
		Timer m_timer;
		double m_solveTime;

		PuzzleDimensions<size> dim;
	};
}
#endif