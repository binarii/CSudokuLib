#ifndef _NAKEDPAIR_H_
#define _NAKEDPAIR_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedPair : public Technique
	{
	public:
		NakedPair();
		~NakedPair();

		int Step(NotchedBoard& board);
	};
}

#endif