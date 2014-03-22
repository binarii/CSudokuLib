#include "NakedTriple.h"

#include "SubsetFinder.h"

namespace sudoku
{
	
	NakedTriple::NakedTriple() :
		Technique(ST_NAKED_TRIPLE)
	{
	}

	NakedTriple::~NakedTriple()
	{

	}

	int NakedTriple::step(Board& board)
	{	
		int useCount = 0;

		useCount = findNakedSubset<3>(board);
		m_useCount += useCount;

		return useCount;
	}
}