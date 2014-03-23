#include "MinDiagonal.h"

#include "../BoardAbstract.h"
#include "../Util.h"

#define TEMPLATE template <int size>
#define TCLASS MinDiagonal<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::MinDiagonal() :
		MinimizeMethod() {

	}

	TEMPLATE
	TCLASS::~MinDiagonal() {

	}

	TEMPLATE
	void TCLASS::minimize(BoardAbstract<size>& board) {	
		// Integer ceiling for divide by 2
		const int boxHeight = (board.UNIT / 2) + (board.UNIT % 2);	

		// Index of center row, right most element
		const int centerIndex = boxHeight * board.UNIT;
		
		const int rate = 2;

		// Initialize array with a[i] = i
		CELL_INDEX shuffleArray[centerIndex];
		for(int i = 0; i < centerIndex; i++) {
			shuffleArray[i] = i;
		}

		util::ArrayShuffle<CELL_INDEX>(shuffleArray, centerIndex);

		CELL_INDEX digArray[centerIndex * rate];

		for(int i = 0; i < centerIndex; i++) {
			// First index
			digArray[i*rate + 0] = i;

			// Count backwards from last index
			digArray[i*rate + 1] = board.GRID - i - 1;
		}

		minimizePattern(board, digArray, centerIndex, rate);
	}

	template class MinDiagonal<2>;
	template class MinDiagonal<3>;
	template class MinDiagonal<4>;
	template class MinDiagonal<5>;
}

#undef TEMPLATE
#undef TCLASS