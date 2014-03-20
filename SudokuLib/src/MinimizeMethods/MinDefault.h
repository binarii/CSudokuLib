#ifndef _MINDEFAULT_H_
#define _MINDEFAULT_H_

#include "../SudokuPrerequisites.h"
#include "../MinimizeMethod.h"

namespace sudoku
{
	template <int size>
	class MinDefault : public MinimizeMethod<size> {
	public:
		MinDefault();
		~MinDefault();

		virtual void minimize(BoardAbstract<size>& board);
	};
}

#endif