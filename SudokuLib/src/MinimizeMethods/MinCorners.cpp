#include "MinCorners.h"

#include "../BoardAbstract.h"
#include "../Util.h"

#define TEMPLATE template <int size>
#define TCLASS MinCorners<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::MinCorners() :
		MinimizeMethod() {

	}

	TEMPLATE
	TCLASS::~MinCorners() {

	}

	TEMPLATE
	void TCLASS::minimize(BoardAbstract<size>& board) {		
		// Size of box reaching half the width and height;
		// Performs integer ceiling for divide by 2
		const int boxWidthHeight = (board.UNIT / 2) + (board.UNIT % 2);
		const int boxArea = boxWidthHeight * boxWidthHeight;
		const int rate = 4;

		// Initialize array with cells of boxArea
		CELL_INDEX shuffleArray[boxArea];
		for(int i = 0; i < boxArea; i++) {
			int x = i % boxArea;
			int y = i / boxArea;
			shuffleArray[i] = (y * board.UNIT) + x;
		}

		util::ArrayShuffle<CELL_INDEX>(shuffleArray, boxArea);

		int x, y;
		int xprime, yprime;
		CELL_INDEX digArray[boxArea * rate];

		for(int i = 0; i < boxArea; i++) {
			// Standard x, y
			x = (shuffleArray[i] / board.UNIT);
			y = shuffleArray[i] % board.UNIT;
			digArray[i*rate + 0] = (y * board.UNIT) + x;


			// Mirror x, y along x axis
			xprime = x;
			yprime = board.UNIT - y - 1;
			digArray[i*rate + 1] = (yprime * board.UNIT) + xprime;


			// Mirror x, y along y axis
			xprime = board.UNIT - x - 1;
			yprime = y;
			digArray[i*rate + 2] = (yprime * board.UNIT) + xprime;


			// Mirror x, y along x and y axis
			xprime = board.UNIT - x - 1;
			yprime = board.UNIT - y - 1;
			digArray[i*rate + 3] = (yprime * board.UNIT) + xprime;
		}

		minimizePattern(board, digArray, boxArea, 2);
	}

	template class MinCorners<2>;
	template class MinCorners<3>;
	template class MinCorners<4>;
	template class MinCorners<5>;
}

#undef TEMPLATE
#undef TCLASS