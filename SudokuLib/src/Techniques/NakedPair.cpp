#include "NakedPair.h"
#include "../Board.h"

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

	int NakedPair::Step(Board<3>& board)
	{	
		int useCount = 0;

		useCount = FindNakedSubset<2, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}