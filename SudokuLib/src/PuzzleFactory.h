#ifndef _PUZZLEFACTORY_H_
#define _PUZZLEFACTORY_H_

#include "SudokuPrerequisites.h"
#include "MinimizeMethod.h"

namespace sudoku
{
	typedef enum {
		ST_DEFAULT,
		ST_DIAGONAL,
		ST_VERTICAL,
		ST_HORIZONTAL,
		ST_CORNERS,
		ST_TOTAL
	} SYMMETRY_TYPE;


	template <int size>
	class PuzzleFactory {
	public:
		PuzzleFactory();
		~PuzzleFactory();

		double minimize(BoardAbstract<size> board, SYMMETRY_TYPE symm, int minClues = 0);

	private:
		typedef MinimizeMethod<size> MinMethod;
		MinMethod* getMinimizer(SYMMETRY_TYPE symm);

	private:
		MinMethod** m_minimizers;
	};
}

#endif