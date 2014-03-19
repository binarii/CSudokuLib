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

	int NakedTriple::Step(BoardAbstract<3>& board)
	{	
		int useCount = 0;

		useCount = FindNakedSubset<3, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}