#include "NakedTriple.h"
#include "../NotchedBoard.h"

#include "SubsetFinder.h"

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
		int useCount = 0;

		useCount = FindNakedSubset<3, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}