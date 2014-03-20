#include "HiddenPair.h"

#include "../BoardAbstract.h"
#include "../BitCount.h"

// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	(bitcount::BitCountArray[x])

namespace sudoku
{
	
	HiddenPair::HiddenPair() :
		Technique(ST_HIDDEN_PAIR)
	{
	}

	HiddenPair::~HiddenPair()
	{

	}

	int HiddenPair::step(Board& board)
	{	
		int useCount = 0;
		
		CELL_INDEX cell1;
		CELL_INDEX cell2;
		BITMASK poss1;
		BITMASK poss2;
		BITMASK combined;

		for(int u = 0; u < board.UNIT*3; ++u)
		{
			for(int c1 = 0; c1 < board.UNIT-1; ++c1)
			{
				cell1 = board.Iterate(u, c1);
				poss1 = board.getCandidates(cell1);
				for(int c2 = c1+1; c2 < board.UNIT; ++c2)
				{
					cell2 = board.Iterate(u, c2);
					poss2 = board.getCandidates(cell2);

					combined = poss1 | poss2;
					int cBitcount = BITCOUNT(combined);

					for(int i = 0; i < board.UNIT; i++)
					{
						if(i == c1 || i == c2)
							continue;

						combined &= ~board.getCandidates(board.Iterate(u, i));
					}

					if(BITCOUNT(combined) == 2 && cBitcount != 2)
					{
						board.mask(cell1, ~combined);
						board.mask(cell2, ~combined);
						useCount++;
						m_useCount++;
					}
				}
			}
		}

		return useCount;
	}
}