#ifndef _NAKEDQUAD_H_
#define _NAKEDQUAD_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedQuad : public Technique {
	public:
		NakedQuad();
		~NakedQuad();

		int step(Board& board);
	};
}

#endif