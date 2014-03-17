#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "Types.h"
#include "PuzzleDimensions.h"
#include "SolveMethod.h"

namespace sudoku
{

	// Solving class
	template <int size>
	class QuickSolve : public PuzzleDimensions<size>, public SolveMethod<size>
	{
	public:
		QuickSolve();
		~QuickSolve();

		int Solve(Board<size>& board);

		void SetMaxSolutionCount(int count);
	private:
		int BacktrackSolve(Board<size>& board);
		int FindSingles(Board<size>& board, CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
	};
}

#endif