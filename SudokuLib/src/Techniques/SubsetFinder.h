#ifndef _SUBSETFINDER_H_
#define _SUBSETFINDER_H_

#include "../SudokuPrerequisites.h"
#include "../BoardAbstract.h"
#include "../BitCount.h"

// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	(bitcount::BitCountArray[x])

namespace sudoku
{
	template <int subsetSize, int UNIT>
	int findNakedSubset(Board& board)
	{
		CELL_INDEX cell1, cell2, cell3, cell4, x;
		BITMASK poss1, poss2, poss3, poss4;
		BITMASK combined;
		int useCount = 0;

		const int UNITmSIZE = UNIT - subsetSize;		

		// For every group
		for(int g = 0; g < UNIT*3; g++)
		{
			for(int c1 = 0; c1 < (UNITmSIZE + 1) && subsetSize > 0; ++c1)
			{
				cell1 = board.iterate(g, c1);
				poss1 = board.getCandidates(cell1);
				if(poss1 == 0) continue; // All cells need be empty

				for(int c2 = c1+1; c2 < (UNITmSIZE + 2) && subsetSize > 1; ++c2)
				{
					cell2 = board.iterate(g, c2);
					poss2 = board.getCandidates(cell2);
					if(poss2 == 0) continue; // All cells need be empty


					// IF SUBSET SIZE IS TWO -----------------------------
					if(subsetSize == 2)
					{
						combined = poss1 | poss2;
						if(BITCOUNT(combined) == 2)
						{
							BITMASK mask = 0;
							for(int i = 0; i < UNIT; ++i)
							{
								if(i == c1 || i == c2) continue;
								x = board.iterate(g, i);
								mask |= board.getCandidates(x) & combined;
								board.mask(x, combined);
							} if(mask) useCount++;							
						}
					} // -------------------------------------------------


					// IF SUBSET SIZE IS GREATER THAN TWO
					for(int c3 = c2+1; c3 < (UNITmSIZE + 3) && subsetSize > 2; ++c3)
					{
						cell3 = board.iterate(g, c3);
						poss3 = board.getCandidates(cell3);
						if(poss3 == 0) continue; // All cells need be empty
						

						// IF SUBSET SIZE IS THREE ---------------------------
						if(subsetSize == 3)
						{
							combined = poss1 | poss2 | poss3;
							if(BITCOUNT(combined) == 3)
							{
								BITMASK mask = 0;
								for(int i = 0; i < UNIT; ++i)
								{
									if(i == c1 || i == c2 || i == c3) continue;
									x = board.iterate(g, i);
									mask |= board.getCandidates(x) & combined;
									board.mask(x, combined);
								} if(mask) useCount++;							
							}
						} // -------------------------------------------------


						// IF SUBSET SIZE IS GREATER THAN THREE
						for(int c4 = c3+1; c4 < (UNITmSIZE + 4) && subsetSize > 3; ++c4)
						{
							cell4 = board.iterate(g, c4);
							poss4 = board.getCandidates(cell4);
							if(poss4 == 0) continue; // All cells need be empty
							

							// IF SUBSET SIZE IS FOUR ----------------------------
							if(subsetSize == 4)
							{
								combined = poss1 | poss2 | poss3 | poss4;
								if(BITCOUNT(combined) == 4)
								{
									BITMASK mask = 0;
									for(int i = 0; i < UNIT; ++i)
									{
										if(i == c1 || i == c2 || i == c3 || i == c4) continue;
										x = board.iterate(g, i);
										mask |= board.getCandidates(x) & combined;
										board.mask(x, combined);
									} if(mask) useCount++;							
								}
							} // -------------------------------------------------

						}
					}
				}
			}
		}
		return useCount;
	}	
}

#endif