#include "SudokuBoard.h"
#include <memory> // memset


// Defines for constants (based on template)
#define BOX  (boxSize)          // Box side length
#define UNIT (BOX * BOX)        // Unit side length (row, col)
#define GRID (UNIT * UNIT)      // Grid size (typical is 81)
#define MASK ((1<<(UNIT+1))-2)  // Mask for all bits except 0


// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	template <int boxSize>
	Board<boxSize>::Board()
	{
		SetCachedArrays();
		Reset();
	}

	template<int boxSize>
	Board<boxSize>::Board(const Board<boxSize>& other)
	{
		m_setCount = other.m_setCount;

		memcpy(m_board, other.m_board, sizeof(m_board));
		memcpy(m_possible, other.m_possible, sizeof(m_possible));
		memcpy(m_rowConflicts, other.m_rowConflicts, sizeof(m_rowConflicts));
		memcpy(m_colConflicts, other.m_colConflicts, sizeof(m_colConflicts));
		memcpy(m_boxConflicts, other.m_boxConflicts, sizeof(m_boxConflicts));
		memcpy(m_rowReference, other.m_rowReference, sizeof(m_rowReference));
		memcpy(m_colReference, other.m_colReference, sizeof(m_colReference));
		memcpy(m_boxReference, other.m_boxReference, sizeof(m_boxReference));
		memcpy(m_groups, other.m_groups, sizeof(m_groups));
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
	void Board<boxSize>::Copy(const Board<boxSize>& other)
	{
		m_setCount = other.m_setCount;

		memcpy(m_board, other.m_board, sizeof(m_board));
		memcpy(m_possible, other.m_possible, sizeof(m_possible));
		memcpy(m_rowConflicts, other.m_rowConflicts, sizeof(m_rowConflicts));
		memcpy(m_colConflicts, other.m_colConflicts, sizeof(m_colConflicts));
		memcpy(m_boxConflicts, other.m_boxConflicts, sizeof(m_boxConflicts));
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