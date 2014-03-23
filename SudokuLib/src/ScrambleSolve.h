#ifndef _SCRAMBLESOLVE_H_
#define _SCRAMBLESOLVE_H_

/**
 * The purpose is to solve the puzzle trying the values in a random order.
 * This will cause unsolved puzzles to be randomized, primarily
 * for use in generating puzzles.
 */

#include "SudokuPrerequisites.h"
#include "SolveMethod.h"

namespace sudoku
{
	template <int size>
	class ScrambleSolve : public SolveMethod<size> {
	public:
		ScrambleSolve();
		~ScrambleSolve();

		int solve(BoardAbstract<size>& board);

	private:
		int backtrackSolve(BoardAbstract<size>& board);
	};
};

#endif