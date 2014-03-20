#ifndef _NAKEDPAIR_H_
#define _NAKEDPAIR_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedPair : public Technique {
	public:
		NakedPair();
		~NakedPair();

		int step(Board& board);
	};
}

#endif