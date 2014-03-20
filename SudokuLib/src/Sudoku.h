#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "PuzzleIndexing.h"
#include "BitCount.h"
#include "Util.h"

#include "SudokuPrerequisites.h"
#include "BoardAbstract.h"
#include "PuzzleFactory.h"
#include "QuickSolve.h"
#include "SudokuGrader.h"


namespace sudoku
{
	inline void Initialize()
	{
		util::Initialize();
		bitcount::Initialize();

		PuzzleIndexing<2>::Initialize();
		PuzzleIndexing<3>::Initialize();
		PuzzleIndexing<4>::Initialize();
		PuzzleIndexing<5>::Initialize();
	}
}


#endif