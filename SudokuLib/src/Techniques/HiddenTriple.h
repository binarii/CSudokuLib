#ifndef _HIDDENTRIPLE_H_
#define _HIDDENTRIPLE_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenTriple : public Technique {
	public:
		HiddenTriple();
		~HiddenTriple();

		int step(Board& board);
	};
}

#endif