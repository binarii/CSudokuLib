#ifndef _NAKEDTRIPLE_H_
#define _NAKEDTRIPLE_H_

#include "SudokuTechnique.h"

namespace sudoku
{
	class NakedTriple : public Technique
	{
	public:
		NakedTriple();
		~NakedTriple();

		int Step(BoardAbstract<3>& board);
	};
}

#endif