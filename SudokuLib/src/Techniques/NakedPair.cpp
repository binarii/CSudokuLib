#include "NakedPair.h"
#include "../NotchedBoard.h"

#include "SubsetFinder.h"

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
		int useCount = 0;

		useCount = FindNakedSubset<2, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}