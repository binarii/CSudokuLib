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
	template <int subsetSize>
	int findNakedSubset(Board& board) {
		CELL_INDEX cells[4] = {-1, -1, -1, -1};

		const BITMASK combined = 0;
		const int lastCell = -1;

		int count = 0;

		for(int i = 0; i < board.UNIT * 3; i++) {
			count += findNakedSingleHelper<subsetSize>(board, subsetSize, lastCell, i, combined, cells);
		}

		return count;
	}

	template <int subsetSize>
	int findNakedSingleHelper(Board& board, const int size, int lastCell, int group, BITMASK combined, CELL_INDEX* cells) {
		const int sizeLessOne = subsetSize - 1;
		const int loopMax = (board.UNIT - sizeLessOne);

		BITMASK candidates;
		int count = 0;

		for(int c = lastCell + 1; c < loopMax; c++) {
			cells[sizeLessOne] = board.iterate(group, c);
			candidates = board.getCandidates(cells[sizeLessOne]);

			if(candidates == 0) {
				continue;
			}

			count += findNakedSingleHelper<sizeLessOne>(board, size, c, group, combined | candidates, cells);
		}

		return count;
	}
	
	template <>
	inline int findNakedSingleHelper<0>(Board& board, const int size, const int lastCell, int group, BITMASK combined, CELL_INDEX* cells) {
		if(BITCOUNT(combined) == size) {
			BITMASK mask = 0;
			for(int i = 0; i < board.UNIT; i++) {
				CELL_INDEX pos = board.iterate(group, i);

				if(pos == cells[0] || pos == cells[1] || pos == cells[2] || pos == cells[3]) {
					continue;
				}

				mask |= board.getCandidates(pos) & combined;
				board.mask(pos, combined);
			}

			return (mask) ? 1 : 0;
		}

		return 0;
	}

	template <int subsetSize>
	int findNakedSubsetOld(Board& board)
	{
		CELL_INDEX cell1, cell2, cell3, cell4, x;
		BITMASK poss1, poss2, poss3, poss4;
		BITMASK combined;
		int useCount = 0;

		const int UNITmSIZE = board.UNIT - subsetSize;		

		// For every group
		for(int g = 0; g < board.UNIT*3; g++)
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
							for(int i = 0; i < board.UNIT; ++i)
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
								for(int i = 0; i < board.UNIT; ++i)
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
									for(int i = 0; i < board.UNIT; ++i)
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