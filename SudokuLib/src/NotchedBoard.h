#ifndef _NOTCHEDBOARD_H_
#define _NOTCHEDBOARD_H_

#include "SudokuBoard.h"

namespace sudoku
{
	class NotchedBoard : public Board<3>
	{
	public:
		NotchedBoard();
		NotchedBoard(const Board<3>& other);
		~NotchedBoard();

		void MaskCell(CELL_INDEX pos, BITMASK mask);
		void ClearMask(CELL_INDEX pos);
		
		// Make sure to call before getting cell possible
		void UpdateCellPossible(CELL_INDEX pos);

	private:
		BITMASK m_boardMask[GRID];
	};
}

#endif