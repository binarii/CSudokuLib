#ifndef _PUZZLEINDEXING_H_
#define _PUZZLEINDEXING_H_

#include "Types.h"
#include "PuzzleDimensions.h"

namespace sudoku
{
	template <int boxSize>
	class PuzzleIndexing : public PuzzleDimensions<boxSize>
	{
	public:
		void InitializeDimensions();
		CELL_INDEX IterateGroups(UNIT_INDEX unit, UNIT_INDEX pos);

	private:
		static bool m_initialized;

	protected:
		static UNIT_INDEX m_rowReference[GRID]; // Stores the row unit index of cell i
		static UNIT_INDEX m_colReference[GRID]; // Stores the col unit index of cell i
		static UNIT_INDEX m_boxReference[GRID]; // Stores the box unit index of cell i

		/**
		 * Helps iterate through units. The first index represents the unit
		 * to choose from (row 0-8, col 9-17, box 18-26 is standard) and the 
		 * second value is the index into this array (typically 0-8), the 
		 * result will be an index on the board of this element.
		 */
		static CELL_INDEX m_groups[UNIT*3][UNIT];
	};
	
	template <int boxSize>
	bool PuzzleIndexing<boxSize>::m_initialized = false;

	template <int boxSize>
	UNIT_INDEX PuzzleIndexing<boxSize>::m_rowReference[PuzzleIndexing<boxSize>::GRID];

	template <int boxSize>
	UNIT_INDEX PuzzleIndexing<boxSize>::m_colReference[PuzzleIndexing<boxSize>::GRID];

	template <int boxSize>
	UNIT_INDEX PuzzleIndexing<boxSize>::m_boxReference[PuzzleIndexing<boxSize>::GRID];

	template <int boxSize>
	UNIT_INDEX PuzzleIndexing<boxSize>::m_groups[PuzzleIndexing<boxSize>::UNIT * 3][PuzzleIndexing<boxSize>::UNIT];

	template <int boxSize>
	void PuzzleIndexing<boxSize>::InitializeDimensions()
	{
		if(m_initialized)
			return;

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
	
	template <int boxSize>
	inline CELL_INDEX PuzzleIndexing<boxSize>::IterateGroups(UNIT_INDEX unit, UNIT_INDEX pos)
	{
		return m_groups[unit][pos];
	}
}

#endif