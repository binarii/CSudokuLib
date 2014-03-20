#ifndef _MINIMIZEMETHOD_H_
#define _MINIMIZEMETHOD_H_

#include "SudokuPrerequisites.h"
#include "Timer.h"

namespace sudoku
{
	template <int size>
	class MinimizeMethod {

	public:
		MinimizeMethod();
		virtual ~MinimizeMethod();

		virtual void minimize(BoardAbstract<size>& board) = 0;

		void startTimer();
		void stopTimer();
		double getTime();
		
		void setMinClueCount(int count);

	protected:
		void minimizePattern(BoardAbstract<size>& board, CELL_INDEX* digArray, int n, int rate);

	protected:
		Timer m_timer;
		double m_solveTime;

		int m_minClueCount;
	};
}

#endif