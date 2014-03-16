#ifndef _SCRAMBLESOLVE_H_
#define _SCRAMBLESOLVE_H_

/**
 * The purpose is to solve the puzzle trying the values in a random order.
 * This will cause unsolved puzzles to be randomized, primarily
 * for use in generating puzzles.
 */

#include "Types.h"
#include "Timer.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;


	template <int size>
	class ScrambleSolve : public PuzzleDimensions<size>
	{
	public:
		ScrambleSolve();
		~ScrambleSolve();

		int solve(Board<size>& board);
		double GetSolveTime();

	private:
		int BacktrackSolve(Board<size>& board);

	private:
		double m_solveTime;
		Timer m_timer;
	};
};

#endif