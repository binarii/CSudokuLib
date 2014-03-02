#ifndef _HIDDENPAIR_H_
#define _HIDDENPAIR_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenPair : public Technique
	{
	public:
		HiddenPair();
		~HiddenPair();

		int Step(NotchedBoard& board);
	};
}

#endif