#ifndef _HIDDENTRIPLE_H_
#define _HIDDENTRIPLE_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenTriple : public Technique
	{
	public:
		HiddenTriple();
		~HiddenTriple();

		int Step(NotchedBoard& board);
	};
}

#endif