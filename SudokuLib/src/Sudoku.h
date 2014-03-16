#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "PuzzleIndexing.h"
#include "BitCount.h"
#include "Util.h"


namespace sudoku
{
	void Initialize()
	{
		util::Initialize();
		bitcount::Initialize;

		PuzzleIndexing<2>::InitIndexing();
		PuzzleIndexing<3>::InitIndexing();
		PuzzleIndexing<4>::InitIndexing();
		PuzzleIndexing<5>::InitIndexing();
	}
}


#endif