#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "SolveMethod.h"

namespace sudoku
{
	template <int size>
	class QuickSolve : public SolveMethod<size> {
	public:
		QuickSolve();
		~QuickSolve();

		int solve(BoardAbstract<size>& board);

		void setMaxSolutionCount(int count);
	private:
		int backtrackSolve(BoardAbstract<size>& board);
		int findSingles(BoardAbstract<size>& board, CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
	};
}

#endif