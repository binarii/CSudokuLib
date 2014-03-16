#ifndef _NAKEDQUAD_H_
#define _NAKEDQUAD_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedQuad : public Technique
	{
	public:
		NakedQuad();
		~NakedQuad();

		int Step(Board<3>& board);
	};
}

#endif