#ifndef _MINVERTICAL_H_
#define _MINVERTICAL_H_

#include "../SudokuPrerequisites.h"
#include "../MinimizeMethod.h"

namespace sudoku
{
	template <int size>
	class MinVertical : public MinimizeMethod<size> {
	public:
		MinVertical();
		~MinVertical();

		virtual void minimize(BoardAbstract<size>& board);
	};
}

#endif