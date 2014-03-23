#include "HiddenTriple.h"

#include "HiddenSubsetFinder.h"

namespace sudoku
{
	
	HiddenTriple::HiddenTriple() :
		Technique(ST_HIDDEN_TRIPLE)
	{
	}

	HiddenTriple::~HiddenTriple()
	{

	}

	int HiddenTriple::step(Board& board)
	{	
		int useCount = 0;

		HiddenSubsetFinder nsFinder;
		useCount = nsFinder.find<3>(board);
		m_useCount += useCount;

		return useCount;
	}
}