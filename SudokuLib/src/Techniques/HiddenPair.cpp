#include "HiddenPair.h"
#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	HiddenPair::HiddenPair() :
		Technique(ST_HIDDEN_PAIR)
	{
	}

	HiddenPair::~HiddenPair()
	{

	}

	int HiddenPair::Step(NotchedBoard& board)
	{	
		int useCount = 0;
		
		CELL_INDEX cell1;
		CELL_INDEX cell2;
		BITMASK poss1;
		BITMASK poss2;
		BITMASK combined;

		for(int u = 0; u < UNIT*3; ++u)
		{
			for(int c1 = 0; c1 < UNIT-1; ++c1)
			{
				cell1 = board.IterateGroups(u, c1);
				poss1 = board.GetCellPossible(cell1);
				for(int c2 = c1+1; c2 < UNIT; ++c2)
				{
					cell2 = board.IterateGroups(u, c2);
					poss2 = board.GetCellPossible(cell2);

					combined = poss1 | poss2;
					int cBitcount = BITCOUNT(combined);

					for(int i = 0; i < UNIT; i++)
					{
						if(i == c1 || i == c2)
							continue;

						combined &= ~board.GetCellPossible(board.IterateGroups(u, i));
					}

					if(BITCOUNT(combined) == 2 && cBitcount != 2)
					{
						board.MaskCell(cell1, ~combined);
						board.MaskCell(cell2, ~combined);
						useCount++;
						m_useCount++;
					}
				}
			}
		}

		return useCount;
	}
}