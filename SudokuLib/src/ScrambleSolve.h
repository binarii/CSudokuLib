#ifndef _SCRAMBLESOLVE_H_
#define _SCRAMBLESOLVE_H_

/**
 * The purpose is to solve the puzzle trying the values in a random order.
 * This will cause unsolved puzzles to be randomized, primarily
 * for use in generating puzzles.
 */

#include "Types.h"
#include "PuzzleDimensions.h"
#include "SolveMethod.h"

namespace sudoku
{
	// Forward the board class
	template <int size>
	class Board;


	template <int size>
	class ScrambleSolve : public SolveMethod<size>
	{
	public:
		ScrambleSolve();
		~ScrambleSolve();

		int Solve(Board<size>& board);

	private:
		int BacktrackSolve(Board<size>& board);
	};
};

#endif