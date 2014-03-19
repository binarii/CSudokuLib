#ifndef _HIDDENPAIR_H_
#define _HIDDENPAIR_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenPair : public Technique
	{
	public:
		HiddenPair();
		~HiddenPair();

		int Step(BoardAbstract<3>& board);
	};
}

#endif