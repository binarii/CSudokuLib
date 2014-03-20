#include "BoardAbstract.h"
#include <memory> // memset

#define TEMPLATE template <int size>
#define TCLASS BoardAbstract<size>

namespace sudoku {

	TEMPLATE
	TCLASS::BoardAbstract() {
		reset();
	}

	TEMPLATE
	TCLASS::BoardAbstract(const BoardAbstract<size>& other) {
		m_setCount = other.m_setCount;

		memcpy(m_gameBoard,    other.m_gameBoard,    sizeof(m_gameBoard));
		memcpy(m_boardMask,    other.m_boardMask,    sizeof(m_boardMask));
		memcpy(m_candidates,   other.m_candidates,   sizeof(m_candidates));
		memcpy(m_rowConflicts, other.m_rowConflicts, sizeof(m_rowConflicts));
		memcpy(m_colConflicts, other.m_colConflicts, sizeof(m_colConflicts));
		memcpy(m_boxConflicts, other.m_boxConflicts, sizeof(m_boxConflicts));
	}

	TEMPLATE
	TCLASS::~BoardAbstract() {

	}

	TEMPLATE
	void TCLASS::reset() {
		memset(&m_gameBoard,    0, sizeof(m_gameBoard));
		memset(&m_boardMask,    0, sizeof(m_boardMask));
		memset(&m_rowConflicts, 0, sizeof(m_rowConflicts));
		memset(&m_colConflicts, 0, sizeof(m_colConflicts));
		memset(&m_boxConflicts, 0, sizeof(m_boxConflicts));
		m_setCount = 0;
	}

	TEMPLATE
	void TCLASS::copy(const BoardAbstract<size>& other) {
		m_setCount = other.m_setCount;

		memcpy(m_gameBoard,    other.m_gameBoard,    sizeof(m_gameBoard));
		memcpy(m_boardMask,    other.m_boardMask,    sizeof(m_boardMask));
		memcpy(m_candidates,   other.m_candidates,   sizeof(m_candidates));
		memcpy(m_rowConflicts, other.m_rowConflicts, sizeof(m_rowConflicts));
		memcpy(m_colConflicts, other.m_colConflicts, sizeof(m_colConflicts));
		memcpy(m_boxConflicts, other.m_boxConflicts, sizeof(m_boxConflicts));
	}

	TEMPLATE
	bool TCLASS::isBoardValid() const {

		// Iterate all the units (27 standard)
		for(int i = 0; i < UNIT * 3; ++i) {
			BITMASK once = 0;
			BITMASK twice = 0;

			// Iterate each cell in the unit
			for(int j = 0; j < UNIT; ++j) {

				// Get the board position
				CELL_INDEX x = iterate(i, j);

				// Get possible mask and value mask
				BITMASK boardVal = getValue(x);

				// Seen twice if current board val and seen once
				twice |= (once & boardVal);

				// Seen once if the current value
				once |= boardVal;
			}

			// Board invalid if any value seen twice
			if(twice) {
				return false;
			}
		}
		return true;
	}

	template class BoardAbstract<2>;
	template class BoardAbstract<3>;
	template class BoardAbstract<4>;
	template class BoardAbstract<5>;
}