#ifndef _BOARD_H_
#define _BOARD_H_

#include "PuzzleIndexing.h"

namespace sudoku
{
	template <int size>
	class BoardAbstract : public PuzzleIndexing<size> {

	public:
		BoardAbstract();
		BoardAbstract(const BoardAbstract<size>& other);
		~BoardAbstract();

		void reset();
		void copy(const BoardAbstract<size>& other);

	public:
		// Basic cell operations
		void remove(CELL_INDEX cell);
		void set   (CELL_INDEX cell, BITMASK val);
		void mask  (CELL_INDEX cell, BITMASK mask);


		// Manage candidates, masks and updates
		void clearMask(CELL_INDEX cell);
		void updateCandidates(CELL_INDEX cell);


		BITMASK getValue     (CELL_INDEX cell) const;
		BITMASK getCandidates(CELL_INDEX cell) const;


		bool isBoardFull()    const;
		bool isBoardValid()   const;
		bool isBoardSolved()  const;
		int  getFilledCount() const;

	private:
		int        m_setCount;            // Number of filled cells
		BITMASK    m_gameBoard[GRID];     // Stores the value placed at each celll
		BITMASK    m_boardMask[GRID];     // Mask values determined to be not allowed in a cell

		BITMASK    m_candidates[GRID];    // Stores candidate values at cell i (from conflicts)
		BITMASK    m_rowConflicts[UNIT];  // Stores the conflicts in row i
		BITMASK    m_colConflicts[UNIT];  // Stores the conflicts in col i
		BITMASK    m_boxConflicts[UNIT];  // Stores the conflicts in box i
	};

	// Typedef the standard size board for ease
	//typedef BoardAbstract<3> Board;


#define TEMPLATE template <int size>
#define TCLASS BoardAbstract<size>

	TEMPLATE
	inline void TCLASS::remove(CELL_INDEX cell) {
		CellReference ref = m_cellReference[cell];
		BITMASK val = ~m_gameBoard[cell];

		m_gameBoard[cell] = 0;
		m_boardMask[cell] = 0;
		m_rowConflicts[ref.row] &= val;
		m_colConflicts[ref.col] &= val;
		m_boxConflicts[ref.box] &= val;
		m_setCount--;
	}

	TEMPLATE
	inline void TCLASS::set(CELL_INDEX cell, BITMASK val) {
		CellReference ref = m_cellReference[cell];

		m_gameBoard[cell] = val;
		m_boardMask[cell] = MASK;
		m_rowConflicts[ref.row] |= val;
		m_colConflicts[ref.col] |= val;
		m_boxConflicts[ref.box] |= val;
		m_setCount++;
	}

	TEMPLATE
	inline void TCLASS::mask(CELL_INDEX cell, BITMASK mask) {
		m_boardMask[cell] |= mask;
	}

	TEMPLATE
	inline void TCLASS::clearMask(CELL_INDEX cell) {
		m_boardMask[cell] = 0;
	}

	TEMPLATE
	inline void TCLASS::updateCandidates(CELL_INDEX cell) {
		CellReference ref = m_cellReference[cell];
		
		m_candidates[cell] = ((~(m_boardMask[cell]       | 
			                     m_rowConflicts[ref.row] |
		                         m_colConflicts[ref.col] |
							     m_boxConflicts[ref.box])) & MASK);
	}

	TEMPLATE
	inline BITMASK TCLASS::getValue(CELL_INDEX cell) const {
		return m_gameBoard[cell];
	}

	TEMPLATE
	inline BITMASK TCLASS::getCandidates(CELL_INDEX cell) const {
		return m_candidates[cell];
	}

	TEMPLATE
	inline bool TCLASS::isBoardFull() const {
		return (m_setCount == GRID);
	}

	TEMPLATE
	inline bool TCLASS::isBoardSolved() const {
		return (isBoardFull() && isBoardValid());
	}

	TEMPLATE
	inline int TCLASS::getFilledCount() const {
		return m_setCount;
	}

#undef TEMPLATE
#undef TCLASS

}

#endif