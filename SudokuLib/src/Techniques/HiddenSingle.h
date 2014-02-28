#ifndef _HIDDENSINGLE_H_
#define _HIDDENSINGLE_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class HiddenSingle : public Technique
	{
	public:
		HiddenSingle();
		~HiddenSingle();

		int Step(NotchedBoard& board);
	};
}

#endif