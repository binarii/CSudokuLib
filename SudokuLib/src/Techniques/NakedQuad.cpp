#include "NakedQuad.h"

#include "SubsetFinder.h"

namespace sudoku
{
	
	NakedQuad::NakedQuad() :
		Technique(ST_NAKED_QUAD)
	{
	}

	NakedQuad::~NakedQuad()
	{

	}

	int NakedQuad::step(Board& board)
	{	
		int useCount = 0;

		useCount = findNakedSubset<4>(board);
		m_useCount += useCount;

		return useCount;
	}
}