#ifndef _SUDOKUTECHNIQUE_H_
#define _SUDOKUTECHNIQUE_H_

#include "../SudokuPrerequisites.h"
#include "TechniqueConstants.h"

namespace sudoku
{
	class Technique {

	public:
		Technique(STRAT_TYPE t) {
			m_useCount = 0;
			m_name = StrategyName[t];
			m_cost = StrategyWeight[t];
		}

		virtual ~Technique() {}

		virtual int step(Board& board) = 0;

		void resetCount() { m_useCount = 0; }
		int getCount()    { return m_useCount; }
		int getCost()     { return m_cost; }
		const char* getName() { return m_name; }
	protected:
		int m_useCount;
		int m_cost;
		const char* m_name;
	};
}

#endif