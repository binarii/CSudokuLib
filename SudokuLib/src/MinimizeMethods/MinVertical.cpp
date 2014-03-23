#include "MinVertical.h"

#include "../BoardAbstract.h"
#include "../Util.h"

#define TEMPLATE template <int size>
#define TCLASS MinVertical<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::MinVertical() :
		MinimizeMethod() {

	}

	TEMPLATE
	TCLASS::~MinVertical() {

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

		int x, y;
		CELL_INDEX digArray[centerIndex * rate];

		for(int i = 0; i < centerIndex; i++) {
			// Standard x, y
			x = (shuffleArray[i] / board.UNIT);
			y = shuffleArray[i] % board.UNIT;

			digArray[i*rate + 0] = (y * board.UNIT) + x;

			// Mirror x, y along y axis
			x = board.UNIT - x - 1;
			y = y;

			digArray[i*rate + 1] = (y * board.UNIT) + x;
		}

		minimizePattern(board, digArray, centerIndex, rate);
	}

	template class MinVertical<2>;
	template class MinVertical<3>;
	template class MinVertical<4>;
	template class MinVertical<5>;
}

#undef TEMPLATE
#undef TCLASS