#include "NakedPair.h"

#include "NakedSubsetFinder.h"

namespace sudoku
{
	
	NakedPair::NakedPair() :
		Technique(ST_NAKED_PAIR)
	{
	}

	NakedPair::~NakedPair()
	{

	}

	int NakedPair::step(Board& board)
	{	
		int useCount = 0;

		NakedSubsetFinder nsFinder;
		useCount = nsFinder.find<2>(board);
		m_useCount += useCount;

		return useCount;
	}
}