#ifndef _MINDIAGONAL_H_
#define _MINDIAGONAL_H_

#include "../SudokuPrerequisites.h"
#include "../MinimizeMethod.h"

namespace sudoku
{
	template <int size>
	class MinDiagonal : public MinimizeMethod<size> {
	public:
		MinDiagonal();
		~MinDiagonal();

		virtual void minimize(BoardAbstract<size>& board);
	};
}

#endif