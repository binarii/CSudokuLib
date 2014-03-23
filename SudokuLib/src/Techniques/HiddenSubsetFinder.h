#ifndef _HIDDENSUBSETFINDER_H_
#define _HIDDENSUBSETFINDER_H_

#include "../SudokuPrerequisites.h"

namespace sudoku
{
	class HiddenSubsetFinder {
	public:
		template <int subsetSize>
		int find(Board& board);

	private:
		template <int iter>
		void findHelper(Board& board, const int size, int lastCell, BITMASK combined);

	private:
		CELL_INDEX m_cells[4];

		int m_counter;
		int m_currentGroup;
	};
}


#endif