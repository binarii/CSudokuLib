#include "HiddenSingle.h"
#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	HiddenSingle::HiddenSingle() :
		Technique(ST_HIDDEN_SINGLE)
	{
	}

	HiddenSingle::~HiddenSingle()
	{

	}

	int HiddenSingle::Step(NotchedBoard& board)
	{	
		CELL_INDEX x;
		int useCount = 0;

		for(int u = 0; u < UNIT*3; ++u)
		{
			BITMASK once = 0;
			BITMASK twice = 0;
			BITMASK all = 0;

			for(int c1 = 0; c1 < UNIT; ++c1)
			{
				// Get the board position
				x = board.IterateGroups(u, c1);

				// Get possible mask and value mask
				board.UpdateCellPossible(x);
				BITMASK possible = board.GetCellPossible(x);
				BITMASK boardVal = board.GetCellValue(x);

				all |= (possible | boardVal);
				twice |= (once & possible);
				once |= possible;
			}

			once &= ~twice;

			if(!once) // If none are seen only once, continue
				continue;
			
			// Find the hidden single
			once &= -once; // Get least set bit
			for(int i = 0; i < UNIT; ++i)
			{
				x = board.IterateGroups(u, i);
				if(board.GetCellPossible(x) & once)
				{
					// Play move and clear possible
					board.SetCell(x, once);
					board.MaskCell(x, MASK);

					m_useCount++;
					useCount++;					
				}
			}
			
		}
		return useCount;
	}
}