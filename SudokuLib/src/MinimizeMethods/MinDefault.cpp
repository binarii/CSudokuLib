#include "MinDefault.h"

#include "../BoardAbstract.h"
#include "../Util.h"

#define TEMPLATE template <int size>
#define TCLASS MinDefault<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::MinDefault() :
		MinimizeMethod() {

	}

	TEMPLATE
	TCLASS::~MinDefault() {

	}

	TEMPLATE
	void TCLASS::minimize(BoardAbstract<size>& board) {	
		const int rate = 1;

		CELL_INDEX digArray[board.GRID];

		// Initialize array with a[i] = i
		for(int i = 0; i < board.GRID; i++) {
			digArray[i] = i;
		}

		util::ArrayShuffle<CELL_INDEX>(digArray, board.GRID);

		// Minimize the board with this pattern
		minimizePattern(board, digArray, board.GRID, rate);
	}

	template class MinDefault<2>;
	template class MinDefault<3>;
	template class MinDefault<4>;
	template class MinDefault<5>;
}

#undef TEMPLATE
#undef TCLASS