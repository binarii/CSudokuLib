#ifndef _MINHORIZONTAL_H_
#define _MINHORIZONTAL_H_

#include "../SudokuPrerequisites.h"
#include "../MinimizeMethod.h"

namespace sudoku
{
	template <int size>
	class MinHorizontal : public MinimizeMethod<size> {
	public:
		MinHorizontal();
		~MinHorizontal();

		virtual void minimize(BoardAbstract<size>& board);
	};
}

#endif