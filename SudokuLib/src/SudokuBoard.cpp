#include "SudokuBoard.h"
#include <memory> // memset

namespace sudoku
{
	template <int boxSize>
	Board<boxSize>::Board()
	{
		SetCachedArrays();
		Reset();
	}
	
	template <int boxSize>
	Board<boxSize>::~Board()
	{

	}

	template <int boxSize>
	void Board<boxSize>::Reset()
	{		
		memset(&m_board, 0, sizeof(m_board));
		memset(&m_rowConflicts, 0, sizeof(m_rowConflicts));
		memset(&m_colConflicts, 0, sizeof(m_colConflicts));
		memset(&m_boxConflicts, 0, sizeof(m_boxConflicts));
		m_setCount = 0;
	}

	template <int boxSize>
	void Board<boxSize>::SetCachedArrays()
	{
		for(int i = 0; i < GRID; i++)
		{
			int col = i % UNIT;
			int row = i / UNIT;
			int box = ((col / BOX) * BOX) + (row / BOX);
			int boxIndex = (col % BOX) + (row % BOX) * BOX;
			m_rowReference[i] = row;
			m_colReference[i] = col;
			m_boxReference[i] = box;
			m_groups[row + UNIT*0][col] = i;
			m_groups[col + UNIT*1][row] = i;
			m_groups[box + UNIT*2][boxIndex] = i;
		}
	}

	template class Board<2>;
	template class Board<3>;
	template class Board<4>;
	template class Board<5>;
}