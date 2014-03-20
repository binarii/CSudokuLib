#ifndef _NAKEDSINGLE_H_
#define _NAKEDSINGLE_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedSingle : public Technique {
	public:
		NakedSingle();
		~NakedSingle();

		int step(Board& board);
	};
}

#endif