#include "NakedSingle.h"
#include "../BoardAbstract.h"
#include "../BitCount.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{	
	NakedSingle::NakedSingle() :
		Technique(ST_NAKED_SINGLE)
	{
	}

	NakedSingle::~NakedSingle()
	{

	}

	int NakedSingle::Step(BoardAbstract<3>& board)
	{		
		int count;
		int useCount = 0;

		BITMASK saveVal = 0;

		for(int i = 0; i < GRID; ++i)
		{

			board.updateCandidates(i);

			if(board.getValue(i) != 0)
				continue;

			BITMASK possible = board.getCandidates(i);

			// Get the bit count for the cell
			count = BITCOUNT(possible);

			// If cell has one possibility play it
			if(count == 1)
			{
				// Play move and clear possible
				board.set(i, possible);

				m_useCount++;
				useCount++;
			}
		}

		return useCount;
	}
}