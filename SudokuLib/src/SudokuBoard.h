#ifndef _SUDOKUBOARD_H_
#define _SUDOKUBOARD_H_

#include "Types.h"
#include "BitCount.h"

#include "PuzzleIndexing.h"

namespace sudoku
{
	template <int boxSize>
	class Board : public PuzzleIndexing<boxSize>
	{
	public:
		Board();
		Board(const Board<boxSize>& other);
		~Board();

		void Reset();
		void Copy(const Board<boxSize>& other);

		// Board Modifiers
		void SetCell(CELL_INDEX pos, BITMASK val);
		void ClearCell(CELL_INDEX pos);

		// Make sure to call before getting cell possible
		virtual void UpdateCellPossible(CELL_INDEX pos);

		// Make a cell have no possibilities (if it is already set)
		virtual void IgnoreCellPossible(CELL_INDEX pos);

		// Get board stats
		int GetSetCount();

		// Get cell stats
		BITMASK GetCellValue(CELL_INDEX pos);
		BITMASK GetCellPossible(CELL_INDEX pos);

	protected:
		int m_setCount;
		BITMASK m_board[GRID];           // Stores the game board

		BITMASK m_possible[GRID];        // Stores possible values at cell i (from conflicts)
		BITMASK m_rowConflicts[UNIT];    // Stores the conflicts in row i
		BITMASK m_colConflicts[UNIT];    // Stores the conflicts in col i
		BITMASK m_boxConflicts[UNIT];    // Stores the conflicts in box i
	};

	template <int boxSize>
	inline void Board<boxSize>::UpdateCellPossible(CELL_INDEX pos)
	{
		m_possible[pos] = ( (~(m_rowConflicts[m_rowReference[pos]] |
		                       m_colConflicts[m_colReference[pos]] |
							   m_boxConflicts[m_boxReference[pos]])) & MASK);
	}

	template <int boxSize>
	inline void Board<boxSize>::IgnoreCellPossible(CELL_INDEX pos)
	{
		m_possible[pos] = 0;
	}

	template <int boxSize>
	inline void Board<boxSize>::SetCell(CELL_INDEX pos, BITMASK val)
	{
		m_board[pos] = val;
		m_rowConflicts[m_rowReference[pos]] |= val;
		m_colConflicts[m_colReference[pos]] |= val;
		m_boxConflicts[m_boxReference[pos]] |= val;
		m_setCount++;
	}

	template <int boxSize>
	inline void Board<boxSize>::ClearCell(CELL_INDEX pos)
	{
		BITMASK val = ~m_board[pos];
		m_board[pos] = 0;
		m_rowConflicts[m_rowReference[pos]] &= val;
		m_colConflicts[m_colReference[pos]] &= val;
		m_boxConflicts[m_boxReference[pos]] &= val;
		m_setCount--;
	}
	
	template <int boxSize>
	inline int Board<boxSize>::GetSetCount()
	{
		return m_setCount;
	}
	
	template <int boxSize>
	inline BITMASK Board<boxSize>::GetCellValue(CELL_INDEX pos)
	{
		return m_board[pos];
	}
	
	template <int boxSize>
	inline BITMASK Board<boxSize>::GetCellPossible(CELL_INDEX pos)
	{
		return m_possible[pos];
	}
}

#endif