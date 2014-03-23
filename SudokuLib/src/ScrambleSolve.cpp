#include "ScrambleSolve.h"
#include "BoardAbstract.h"
#include "Util.h"

namespace sudoku
{	
	template <int size>
	ScrambleSolve<size>::ScrambleSolve() {
		m_solveTime = 0.0;
	}

	template <int size>
	ScrambleSolve<size>::~ScrambleSolve() {

	}

	template <int size>
	int ScrambleSolve<size>::solve(BoardAbstract<size>& board) {
		startTimer();
		int solutionCount = backtrackSolve(board);
		stopTimer();

		return solutionCount;
	}

	template <int size>
	int ScrambleSolve<size>::backtrackSolve(BoardAbstract<size>& board) {
		if(board.isBoardFull()) {
			return 1;
		}

		int solutionsFound = 0;
		CELL_INDEX pos = board.getFilledCount();

		// Get the possible values for the cell
		board.updateCandidates(pos);
		BITMASK possible = board.getCandidates(pos);

		// Choose the order to try values
		BITMASK cellOrder[dim.UNIT];
		for(int i = 0; i < dim.UNIT; i++) {
			cellOrder[i] = (1 << (i + 1));
		}

		util::ArrayShuffle<BITMASK>(cellOrder, dim.UNIT);

		// Go through values and recursively try them
		for(int i = 0; i < dim.UNIT; i++) {
			if(cellOrder[i] & possible) {

				board.set(pos, cellOrder[i]);
				solutionsFound = backtrackSolve(board);

				if(solutionsFound > 0) {
					return solutionsFound;
				}

				board.remove(pos);

				possible &= ~cellOrder[i];
			}
		}
		return 0;
	}

	template class ScrambleSolve<2>;
	template class ScrambleSolve<3>;
	template class ScrambleSolve<4>;
	template class ScrambleSolve<5>;
}