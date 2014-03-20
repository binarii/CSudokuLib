#include "HiddenSingle.h"

#include "../BoardAbstract.h"
#include "../BitCount.h"

// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	(bitcount::BitCountArray[x])

namespace sudoku
{
	
	HiddenSingle::HiddenSingle() :
		Technique(ST_HIDDEN_SINGLE)
	{
	}

	HiddenSingle::~HiddenSingle()
	{

	}

	int HiddenSingle::step(Board& board)
	{	
		CELL_INDEX x;
		int useCount = 0;

		for(int u = 0; u < board.UNIT*3; ++u)
		{
			BITMASK once = 0;
			BITMASK twice = 0;
			BITMASK all = 0;

			for(int c1 = 0; c1 < board.UNIT; ++c1)
			{
				// Get the board position
				x = board.Iterate(u, c1);

				// Get possible mask and value mask
				board.updateCandidates(x);
				BITMASK possible = board.getCandidates(x);
				BITMASK boardVal = board.getValue(x);

				all |= (possible | boardVal);
				twice |= (once & possible);
				once |= possible;
			}

			once &= ~twice;

			if(!once) // If none are seen only once, continue
				continue;
			
			// Find the hidden single
			once = getLSB(once); // Get least set bit
			for(int i = 0; i < board.UNIT; ++i)
			{
				x = board.Iterate(u, i);
				if(board.getCandidates(x) & once)
				{
					// Play move and clear possible
					board.set(x, once);

					m_useCount++;
					useCount++;					
				}
			}
			
		}
		return useCount;
	}
}