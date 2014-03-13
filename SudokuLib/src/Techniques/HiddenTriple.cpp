#include "HiddenTriple.h"
#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	HiddenTriple::HiddenTriple() :
		Technique(ST_HIDDEN_TRIPLE)
	{
	}

	HiddenTriple::~HiddenTriple()
	{

	}

	int HiddenTriple::Step(NotchedBoard& board)
	{	
		int useCount = 0;
		
		CELL_INDEX cell1;
		CELL_INDEX cell2;
		CELL_INDEX cell3;
		BITMASK poss1;
		BITMASK poss2;
		BITMASK poss3;
		BITMASK combined;

		for(int u = 0; u < UNIT*3; ++u)
		{
			for(int c1 = 0; c1 < UNIT-2; ++c1)
			{
				cell1 = board.IterateGroups(u, c1);
				poss1 = board.GetCellPossible(cell1);
				for(int c2 = c1+1; c2 < UNIT-1; ++c2)
				{
					cell2 = board.IterateGroups(u, c2);
					poss2 = board.GetCellPossible(cell2);
					for(int c3 = c2+1; c3 < UNIT; ++c3)
					{

						cell3 = board.IterateGroups(u, c3);
						poss3 = board.GetCellPossible(cell3);
					
						combined = poss1 | poss2 | poss3;
						int cBitcount = BITCOUNT(combined);

						for(int i = 0; i < UNIT; i++)
						{
							if(i == c1 || i == c2 || i == c3)
								continue;

							combined &= ~board.GetCellPossible(board.IterateGroups(u, i));
						}

						if(BITCOUNT(combined) == 3 && cBitcount != 3)
						{
							board.MaskCell(cell1, ~combined);
							board.MaskCell(cell2, ~combined);
							board.MaskCell(cell3, ~combined);
							useCount++;
							m_useCount++;
						}
					}
				}
			}
		}

		return useCount;
	}
}