#ifndef _SUDOKUBOARD_H_
#define _SUDOKUBOARD_H_

#include "Types.h"
#include "BitCount.h"


// Defines for constants (based on template)
#define BOX  (boxSize)          // Box side length
#define UNIT (BOX * BOX)        // Unit side length (row, col)
#define GRID (UNIT * UNIT)      // Grid size (typical is 81)
#define MASK ((1<<(UNIT+1))-2)  // Mask for all bits except 0


// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount())


namespace sudoku
{
	template <int boxSize>
	class Board
	{
	public:
		Board();
		~Board();

		void Reset();

		// Board Modifiers
		void SetCell(CELL_INDEX pos, BITMASK val);
		void ClearCell(CELL_INDEX pos);

		// Make sure to call before getting cell possible
		void UpdateCellPossible(CELL_INDEX pos);

		// Make a cell have no possibilities (if it is already set)
		void IgnoreCellPossible(CELL_INDEX pos);

		// Get board stats
		int GetSetCount();

		// Get cell stats
		BITMASK GetCellMask(CELL_INDEX pos);
		BITMASK GetCellPossible(CELL_INDEX pos);

		// Help iteration through cells
		CELL_INDEX IterateGroups(UNIT_INDEX unit, UNIT_INDEX pos);

	private:
		void SetCachedArrays();

	private:
		int m_setCount;
		BITMASK m_board[GRID];           // Stores the game board

		BITMASK m_possible[GRID];        // Stores possible values at cell i (from conflicts)
		BITMASK m_rowConflicts[UNIT];    // Stores the conflicts in row i
		BITMASK m_colConflicts[UNIT];    // Stores the conflicts in col i
		BITMASK m_boxConflicts[UNIT];    // Stores the conflicts in box i

		UNIT_INDEX m_rowReference[GRID]; // Stores the row unit index of cell i
		UNIT_INDEX m_colReference[GRID]; // Stores the col unit index of cell i
		UNIT_INDEX m_boxReference[GRID]; // Stores the box unit index of cell i

		/**
		 * Helps iterate through units. The first index represents the unit
		 * to choose from (row 0-8, col 9-17, box 18-26 is standard) and the 
		 * second value is the index into this array (typically 0-8), the 
		 * result will be an index on the board of this element.
		 */
		CELL_INDEX m_groups[UNIT*3][UNIT]; 
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
	inline BITMASK Board<boxSize>::GetCellMask(CELL_INDEX pos)
	{
		return m_board[pos];
	}
	
	template <int boxSize>
	inline BITMASK Board<boxSize>::GetCellPossible(CELL_INDEX pos)
	{
		return m_possible[pos];
	}
	
	template <int boxSize>
	inline CELL_INDEX Board<boxSize>::IterateGroups(UNIT_INDEX unit, UNIT_INDEX pos)
	{
		return m_groups[unit][pos];
	}
}

#endif