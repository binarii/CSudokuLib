#ifndef _SOLVEMETHOD_H_
#define _SOLVEMETHOD_H_

#include "Timer.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;


	template <int size>
	class SolveMethod
	{
	public:
		virtual int Solve(Board<size>& board) = 0;

		void StartTimer() { m_timer.StartTimer(); }
		void StopTimer() { m_solveTime = m_timer.GetTime(); }
		double GetTime() { return m_solveTime; }

	protected:
		Timer m_timer;
		double m_solveTime;
	};
}
#endif