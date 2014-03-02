#include "NotchedBoard.h"
#include <memory>

namespace sudoku
{	
	NotchedBoard::NotchedBoard() :
		Board()
	{
		Reset();
	}
		
	NotchedBoard::NotchedBoard(const Board<3>& other) :
		Board(other)
	{
		memset(&m_boardMask, 0, sizeof(m_boardMask));

		for(int i = 0; i < GRID; i++)
			if(m_board[i] != 0)
				m_boardMask[i] = MASK;
	}

	NotchedBoard::~NotchedBoard()
	{

	}

	void NotchedBoard::MaskCell(CELL_INDEX pos, BITMASK mask)
	{
		m_boardMask[pos] |= mask;
	}

	void NotchedBoard::ClearMask(CELL_INDEX pos)
	{
		m_boardMask[pos] = 0;
	}

	void NotchedBoard::UpdateCellPossible(CELL_INDEX pos)
	{
		m_possible[pos] = ( (~(m_boardMask[pos] | 
			                   m_rowConflicts[m_rowReference[pos]] |
		                       m_colConflicts[m_colReference[pos]] |
							   m_boxConflicts[m_boxReference[pos]])) & MASK);
	}
}