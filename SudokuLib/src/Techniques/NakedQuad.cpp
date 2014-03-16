#include "NakedQuad.h"
#include "../Board.h"

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

	int NakedQuad::Step(Board<3>& board)
	{	
		int useCount = 0;

		useCount = FindNakedSubset<4, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}