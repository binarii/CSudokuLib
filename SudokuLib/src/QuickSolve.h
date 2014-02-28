#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "Types.h"
#include "Timer.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
	// Forward the board class
	template <int boxSize>
	class Board;

	// Solving class
	template <int boxSize>
	class QuickSolve : PuzzleDimensions<boxSize>
	{
	public:
		QuickSolve();
		~QuickSolve();

		int Solve(Board<boxSize>& board);
		double GetSolveTime();

		void SetMaxSolutionCount(int count);
	private:
		int BacktrackSolve(Board<boxSize>& board);
		int FindSingles(Board<boxSize>& board, CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
		double m_solveTime;

		Timer m_timer;
	};
}

#endif