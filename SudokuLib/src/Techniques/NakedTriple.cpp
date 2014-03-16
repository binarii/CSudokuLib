#include "NakedTriple.h"
#include "../Board.h"

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

	int NakedTriple::Step(Board<3>& board)
	{	
		int useCount = 0;

		useCount = FindNakedSubset<3, UNIT>(board);
		m_useCount += useCount;

		return useCount;
	}
}