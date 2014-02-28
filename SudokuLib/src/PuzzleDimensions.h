#ifndef _PUZZLEDIMENSIONS_H_
#define _PUZZLEDIMENSIONS_H_

namespace sudoku
{
	template <int boxSize>
	class PuzzleDimensions
	{
	public:
		static const int BOX = boxSize;
		static const int UNIT = BOX * BOX;
		static const int GRID = UNIT * UNIT;
		static const BITMASK MASK = ((1 << (UNIT + 1)) - 2);
	};
}

#endif