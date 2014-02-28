#include "SudokuBoard.h"
#include <memory> // memset

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	template <int boxSize>
	Board<boxSize>::Board()
	{
		InitializeDimensions();
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

		InitializeDimensions();
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

	template class Board<2>;
	template class Board<3>;
	template class Board<4>;
	template class Board<5>;
}