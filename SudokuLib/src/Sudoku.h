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

		PuzzleIndexing<2>::initialize();
		PuzzleIndexing<3>::initialize();
		PuzzleIndexing<4>::initialize();
		PuzzleIndexing<5>::initialize();
	}
}


#endif