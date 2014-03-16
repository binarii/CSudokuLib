#ifndef _SUDOKUTECHNIQUE_H_
#define _SUDOKUTECHNIQUE_H_

#include "../PuzzleDimensions.h"
#include "TechniqueConstants.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;

	class Technique : public PuzzleDimensions<3>
	{
	public:
		Technique(STRAT_TYPE t)
		{
			m_useCount = 0;
			m_name = StrategyName[t];
			m_cost = StrategyWeight[t];
		}

		virtual int Step(Board<3>& board) = 0;

		void ResetCount() { m_useCount = 0; }
		int GetCount() { return m_useCount; }
		int GetCost() { return m_cost; }
		const char* GetName() { return m_name; }
	protected:
		int m_useCount;
		int m_cost;
		const char* m_name;
	};
}

#endif