#include "NakedSingle.h"
#include "NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{	
	NakedSingle::NakedSingle()
	{
		m_cost = 1;
		m_useCount = 0;
	}

	NakedSingle::~NakedSingle()
	{

	}

	int NakedSingle::Step(NotchedBoard& board)
	{		
		int count;
		int useCount = 0;

		BITMASK saveVal = 0;

		for(int i = 0; i < GRID; ++i)
		{
			if(board.GetCellValue(i) != 0)
				continue;

			// Get the possible values
			board.UpdateCellPossible(i);
			BITMASK possible = board.GetCellPossible(i);

			// Get the bit count for the cell
			count = BITCOUNT(possible);

			// If cell has one possibility play it
			if(count == 1)
			{
				// Play move and clear possible
				board.SetCell(i, possible);
				board.IgnoreCellPossible(i);

				m_useCount++;
				useCount++;
			}
		}

		return useCount;
	}
}