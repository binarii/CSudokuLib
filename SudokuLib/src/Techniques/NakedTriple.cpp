#include "NakedTriple.h"

#include "NakedSubsetFinder.h"

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
		
		NakedSubsetFinder nsFinder;
		useCount = nsFinder.find<3>(board);
		m_useCount += useCount;

		return useCount;
	}
}