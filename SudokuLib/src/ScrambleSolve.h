#ifndef _SCRAMBLESOLVE_H_
#define _SCRAMBLESOLVE_H_

/**
 * The purpose is to solve the puzzle trying the values in a random order.
 * This will cause unsolved puzzles to be randomized, primarily
 * for use in generating puzzles.
 */


#include "Types.h"
#include "Timer.h"

namespace sudoku
{
	// Forward the board class
	template <int boxSize>
	class Board;

	template <int boxSize>
	class ScrambleSolve
	{
	public:
		ScrambleSolve();
		~ScrambleSolve();

		int solve(Board<boxSize>& board);
		double GetSolveTime();

	private:
		int BacktrackSolve(Board<boxSize>& board);

	private:
		double m_solveTime;
		Timer m_timer;
	};
};

#endif