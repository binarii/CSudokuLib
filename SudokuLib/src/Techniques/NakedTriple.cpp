#include "NakedTriple.h"
#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	NakedTriple::NakedTriple() :
		Technique(ST_NAKED_TRIPLE)
	{
	}

	NakedTriple::~NakedTriple()
	{

	}

	int NakedTriple::Step(NotchedBoard& board)
	{	
		CELL_INDEX cell1;
		CELL_INDEX cell2;
		CELL_INDEX cell3;
		BITMASK poss1;
		BITMASK poss2;
		BITMASK poss3;
		BITMASK combine;
		int useCount = 0;		

		for(int i = 0; i < UNIT; i++)
			board.UpdateCellPossible(i);

		for(int i = 0; i < UNIT*3; ++i)
		{
			for(int c1 = 0; c1 < UNIT-2; ++c1)
			{				
				// Get the board position
				cell1 = board.IterateGroups(i, c1);
				poss1 = board.GetCellPossible(cell1);

				for(int c2 = c1+1; c2 < UNIT-1; c2++)
				{
					cell2 = board.IterateGroups(i, c2);
					poss2 = board.GetCellPossible(cell2);

					for(int c3 = c2+1; c3 < UNIT; c3++)
					{						
						cell3 = board.IterateGroups(i, c3);
						poss3 = board.GetCellPossible(cell3);

						if(poss1 == 0 || poss2 == 0 || poss3 == 0)
							continue;

						combine = cell1 | cell2 | cell3;

						// Weve found a triple
						if(BITCOUNT(combine) == 3)
						{
							BITMASK mask = 0;
							for(int u = 0; u < UNIT; u++)
							{
								if(u == c1 || u == c2 || u == c3)
									continue;
								
								mask |= board.GetCellPossible(board.IterateGroups(i, u)) & combine;
								board.MaskCell(board.IterateGroups(i, u), combine);	
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
		}
		return useCount;
	}
}