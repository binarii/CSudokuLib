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

		for(int i = 0; i < UNIT*3; ++i)
		{

			BITMASK once = 0;
			BITMASK twice = 0;
			BITMASK all = 0;

			for(int j = 0; j < UNIT; ++j)
			{
				// Get the board position
				x = board.IterateGroups(i, j);

				// Get possible mask and value mask
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
			for(int j = 0; j < UNIT; ++j)
			{
				x = board.IterateGroups(i, j);
				if(board.GetCellPossible(x) & once)
				{
					// Play move and clear possible
					board.SetCell(x, once);
					board.IgnoreCellPossible(x);

					m_useCount++;
					useCount++;					
				}
			}
			
		}
		return useCount;
	}
}