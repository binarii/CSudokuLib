#include "NakedPair.h"

#include "SubsetFinder.h"

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

		useCount = findNakedSubset<2>(board);
		m_useCount += useCount;

		return useCount;
	}
}