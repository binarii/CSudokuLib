#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "SolveMethod.h"

namespace sudoku
{
	template <int size>
	class QuickSolve : public SolveMethod<size>
	{
	public:
		QuickSolve();
		~QuickSolve();

		int Solve(BoardAbstract<size>& board);

		void SetMaxSolutionCount(int count);
	private:
		int BacktrackSolve(BoardAbstract<size>& board);
		int FindSingles(BoardAbstract<size>& board, CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
	};
}

#endif