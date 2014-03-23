#ifndef _MINCORNERS_H_
#define _MINCORNERS_H_

#include "../SudokuPrerequisites.h"
#include "../MinimizeMethod.h"

namespace sudoku
{
	template <int size>
	class MinCorners : public MinimizeMethod<size> {
	public:
		MinCorners();
		~MinCorners();

		virtual void minimize(BoardAbstract<size>& board);
	};
}

#endif