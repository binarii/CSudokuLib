#ifndef _BOARD_H_
#define _BOARD_H_

#include "PuzzleIndexing.h"

namespace sudoku
{
	template <int size>
	class Board : public PuzzleIndexing<size>
	{
	public:
		Board();
		Board(const Board<size>& other);
		~Board();

		void Reset();
		void Copy(const Board<size>& other);

	public:
		void Remove(CELL_INDEX cell);
		void Set   (CELL_INDEX cell, BITMASK val);
		void Mask  (CELL_INDEX cell, BITMASK mask);


		void ClearMask(CELL_INDEX cell);
		void UpdateCandidates(CELL_INDEX cell);


		BITMASK GetValue     (CELL_INDEX cell) const;
		BITMASK GetCandidates(CELL_INDEX cell) const;


		bool BoardFull()      const;
		bool BoardValid()     const;
		int  GetFilledCount() const;

	private:
		int        m_setCount;            // Number of filled cells
		BITMASK    m_board[GRID];         // Stores the game board
		BITMASK    m_boardMask[GRID];     // Allows masking of cells

		BITMASK    m_candidates[GRID];    // Stores candidate values at cell i (from conflicts)
		BITMASK    m_rowConflicts[UNIT];  // Stores the conflicts in row i
		BITMASK    m_colConflicts[UNIT];  // Stores the conflicts in col i
		BITMASK    m_boxConflicts[UNIT];  // Stores the conflicts in box i
	};



#define TEMPLATE template <int size>
#define TCLASS Board<size>

	TEMPLATE
	inline void TCLASS::Remove(CELL_INDEX cell)
	{
		CellReference ref = m_cellReference[cell];
		BITMASK val = ~m_board[cell];

		m_board[cell] = 0;
		m_boardMask[cell] = 0;
		m_rowConflicts[ref.row] &= val;
		m_colConflicts[ref.col] &= val;
		m_boxConflicts[ref.box] &= val;
		m_setCount--;
	}

	TEMPLATE
	inline void TCLASS::Set(CELL_INDEX cell, BITMASK val)
	{
		CellReference ref = m_cellReference[cell];

		m_board[cell] = val;
		m_boardMask[cell] = MASK;
		m_rowConflicts[ref.row] |= val;
		m_colConflicts[ref.col] |= val;
		m_boxConflicts[ref.box] |= val;
		m_setCount++;
	}

	TEMPLATE
	inline void TCLASS::Mask(CELL_INDEX cell, BITMASK mask)
	{
		m_boardMask[cell] |= mask;
	}

	TEMPLATE
	inline void TCLASS::ClearMask(CELL_INDEX cell)
	{
		m_boardMask[cell] = 0;
	}

	TEMPLATE
	inline void TCLASS::UpdateCandidates(CELL_INDEX cell)
	{
		CellReference ref = m_cellReference[cell];
		
		m_candidates[cell] = ((~(m_boardMask[cell]       | 
			                     m_rowConflicts[ref.row] |
		                         m_colConflicts[ref.col] |
							     m_boxConflicts[ref.box])) & MASK);
	}

	TEMPLATE
	inline BITMASK TCLASS::GetValue(CELL_INDEX cell) const
	{
		return m_board[cell];
	}

	TEMPLATE
	inline BITMASK TCLASS::GetCandidates(CELL_INDEX cell) const
	{
		return m_candidates[cell];
	}

	TEMPLATE
	inline bool TCLASS::BoardFull() const
	{
		return m_setCount == GRID;
	}

	TEMPLATE
	inline bool TCLASS::BoardValid() const
	{
		return true;
	}

	TEMPLATE
	inline int TCLASS::GetFilledCount() const
	{
		return m_setCount;
	}

#undef TEMPLATE
#undef TCLASS

}

#endif