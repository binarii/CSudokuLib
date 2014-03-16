#ifndef _NAKEDTRIPLE_H_
#define _NAKEDTRIPLE_H_

#include "../Types.h"
#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedTriple : public Technique
	{
	public:
		NakedTriple();
		~NakedTriple();

		int Step(Board<3>& board);
	};
}

#endif