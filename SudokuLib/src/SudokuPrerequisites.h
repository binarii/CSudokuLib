#ifndef _SUDOKUPREREQUISITES_H_
#define _SUDOKUPREREQUISITES_H_

#include "Types.h"

namespace sudoku
{
	template <int size>
	class BoardAbstract;

	typedef BoardAbstract<3> Board;

	template <int size>
	class SolveMethod;

	template <int size>
	class QuickSolve;

	template <int size>
	class ScrambleSolve;

	class Technique;
}


#endif