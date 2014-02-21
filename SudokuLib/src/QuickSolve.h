#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "Types.h"

namespace sudoku
{
	// Forward the board class
	template <int boxSize>
	class Board;

	// Solving class
	template <int boxSize>
	class QuickSolve
	{
	public:
		QuickSolve();
		~QuickSolve();

		int Solve(Board<boxSize>& board);

	private:
		int BacktrackSolve(Board<boxSize>& board);
		int FindSingles(CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
		double m_solveTime;
	};
}

#endif