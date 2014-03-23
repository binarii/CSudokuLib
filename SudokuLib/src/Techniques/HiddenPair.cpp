#include "HiddenPair.h"

#include "HiddenSubsetFinder.h"

namespace sudoku
{
	
	HiddenPair::HiddenPair() :
		Technique(ST_HIDDEN_PAIR)
	{
	}

	HiddenPair::~HiddenPair()
	{

	}

	int HiddenPair::step(Board& board)
	{	
		int useCount = 0;

		HiddenSubsetFinder nsFinder;
		useCount = nsFinder.find<2>(board);
		m_useCount += useCount;

		return useCount;
	}
}