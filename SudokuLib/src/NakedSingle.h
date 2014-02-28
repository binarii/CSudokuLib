#ifndef _NAKEDSINGLE_H_
#define _NAKEDSINGLE_H_

#include "Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedSingle : public Technique
	{
	public:
		NakedSingle();
		~NakedSingle();

		int Step(NotchedBoard& board);
	};
}

#endif