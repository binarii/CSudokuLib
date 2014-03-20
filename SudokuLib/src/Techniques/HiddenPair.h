#ifndef _HIDDENPAIR_H_
#define _HIDDENPAIR_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenPair : public Technique {
	public:
		HiddenPair();
		~HiddenPair();

		int step(Board& board);
	};
}

#endif