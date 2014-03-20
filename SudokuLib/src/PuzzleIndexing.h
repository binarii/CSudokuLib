#ifndef _PUZZLEINDEXING_H_
#define _PUZZLEINDEXING_H_

#include "Types.h"
#include "PuzzleDimensions.h"

namespace sudoku
{

	template <int size>
	class PuzzleIndexing : public PuzzleDimensions<size>
	{
	public:
		static void Initialize();

		CELL_INDEX Iterate(UNIT_INDEX unit, UNIT_INDEX pos) const;

	private:
		static bool m_initialized;

	protected:
		// Stores the row, col, and box reference for cell i
		static CellReference m_cellReference[GRID]; 

		static const int GROUP_COUNT = UNIT * 3;
		static const int GROUP_WIDTH = UNIT;

		/**
		 * Helps iterate through units. The first index represents the unit
		 * to choose from (row 0-8, col 9-17, box 18-26 is standard) and the 
		 * second value is the index into this array (typically 0-8), the 
		 * result will be an index on the board of this element.
		 */
		static CELL_INDEX m_groups[GROUP_COUNT * GROUP_WIDTH];
	};
	

	template <int size>
	bool PuzzleIndexing<size>::m_initialized = false;

	template <int size>
	CellReference PuzzleIndexing<size>::m_cellReference[PuzzleIndexing<size>::GRID];

	template <int size>
	CELL_INDEX PuzzleIndexing<size>::m_groups[PuzzleIndexing<size>::GROUP_COUNT * PuzzleIndexing<size>::GROUP_WIDTH];


	template <int size>
	void PuzzleIndexing<size>::Initialize()
	{
		if(m_initialized)
			return;

		for(int i = 0; i < GRID; i++)
		{
			CellReference ref;
			ref.col = i % UNIT;
			ref.row = i / UNIT;
			ref.box = ((ref.col / BOX) * BOX) + (ref.row / BOX);

			int boxIndex = (ref.col % BOX) + (ref.row % BOX) * BOX;
			m_cellReference[i] = ref;
			m_groups[(ref.row + UNIT*0) * GROUP_WIDTH + ref.col]  = i;
			m_groups[(ref.col + UNIT*1) * GROUP_WIDTH + ref.row]  = i;
			m_groups[(ref.box + UNIT*2) * GROUP_WIDTH + boxIndex] = i;
		}
	}
	
	template <int size>
	inline CELL_INDEX PuzzleIndexing<size>::Iterate(UNIT_INDEX unit, UNIT_INDEX pos) const
	{
		return m_groups[unit * GROUP_WIDTH + pos];
	}
}

#endif