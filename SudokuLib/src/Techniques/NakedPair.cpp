#include "NakedPair.h"
#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	NakedPair::NakedPair() :
		Technique(ST_NAKED_PAIR)
	{
	}

	NakedPair::~NakedPair()
	{

	}

	int NakedPair::Step(NotchedBoard& board)
	{	
		CELL_INDEX cell1;
		CELL_INDEX cell2;
		BITMASK poss1;
		BITMASK poss2;
		int useCount = 0;

		for(int i = 0; i < UNIT; i++)
			board.UpdateCellPossible(i);

		for(int i = 0; i < UNIT*3; ++i)
		{
			for(int j = 0; j < UNIT-1; ++j)
			{				
				// Get the board position
				cell1 = board.IterateGroups(i, j);
				poss1 = board.GetCellPossible(cell1);

				for(int k = j+1; k < UNIT; k++)
				{
					cell2 = board.IterateGroups(i, k);
					poss2 = board.GetCellPossible(cell2);

					// weve found a pair
					if(poss1 == poss2 && BITCOUNT(poss1) == 2)
					{
						BITMASK mask = 0;
						for(int u = 0; u < UNIT; u++)
						{
							if(u == j || u == k)
								continue;

							mask |= board.GetCellPossible(board.IterateGroups(i, u)) & poss2;
							board.MaskCell(board.IterateGroups(i, u), poss2);
							board.UpdateCellPossible(board.IterateGroups(i, u));
						}

						if(mask)
						{
							m_useCount++;
							useCount++;
						}
					}					
				}
			}
		}
		return useCount;
	}
}