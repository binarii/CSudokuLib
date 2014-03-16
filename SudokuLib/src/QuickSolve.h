#ifndef _QUICKSOLVE_H_
#define _QUICKSOLVE_H_

#include "Types.h"
#include "Timer.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;

	// Solving class
	template <int size>
	class QuickSolve : public PuzzleDimensions<size>
	{
	public:
		QuickSolve();
		~QuickSolve();

		int Solve(Board<size>& board);
		double GetSolveTime();

		void SetMaxSolutionCount(int count);
	private:
		int BacktrackSolve(Board<size>& board);
		int FindSingles(Board<size>& board, CELL_INDEX& pos, BITMASK& value);

	private:
		int m_maxSolutions;
		double m_solveTime;

		Timer m_timer;
	};
}

#endif