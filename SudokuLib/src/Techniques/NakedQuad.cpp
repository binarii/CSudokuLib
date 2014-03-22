#include "NakedQuad.h"

#include "NakedSubsetFinder.h"

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
		
		NakedSubsetFinder nsFinder;
		useCount = nsFinder.find<4>(board);
		m_useCount += useCount;

		return useCount;
	}
}