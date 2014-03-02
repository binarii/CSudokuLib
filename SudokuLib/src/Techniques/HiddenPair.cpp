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

		for(int i = 0; i < UNIT; i++)
			board.UpdateCellPossible(i);

		for(int i = 0; i < UNIT*3; i++)
		{
			for(int j = 0; j < UNIT-1; j++)
			{
				cell1 = board.IterateGroups(i, j);
				poss1 = board.GetCellPossible(cell1);
				for(int k = j+1; k < UNIT; k++)
				{
					cell2 = board.IterateGroups(i, k);
					poss2 = board.GetCellPossible(cell2);

					combined = poss1 | poss2;
					int cBitcount = BITCOUNT(combined);

					for(int u = 0; u < UNIT; u++)
					{
						if(u == j || u == k)
							continue;

						combined &= ~board.GetCellPossible(board.IterateGroups(i, u));
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