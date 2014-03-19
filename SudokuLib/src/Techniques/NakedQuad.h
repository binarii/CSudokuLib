#ifndef _NAKEDQUAD_H_
#define _NAKEDQUAD_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedQuad : public Technique
	{
	public:
		NakedQuad();
		~NakedQuad();

		int Step(BoardAbstract<3>& board);
	};
}

#endif