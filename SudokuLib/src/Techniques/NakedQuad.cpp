#include "NakedQuad.h"
#include "../NotchedBoard.h"

#include "SubsetFinder.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	((BOX < 4) ? bitcount::BitCountArray[x] : bitcount::BitCount(x))

namespace sudoku
{
	
	NakedQuad::NakedQuad() :
		Technique(ST_NAKED_QUAD)
	{
	}

	NakedQuad::~NakedQuad()
	{

	}

	int NakedQuad::Step(NotchedBoard& board)
	{	
		int useCount = 0;

		useCount = FindNakedSubset<4, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}