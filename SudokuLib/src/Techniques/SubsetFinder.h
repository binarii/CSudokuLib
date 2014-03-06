#ifndef _SUBSETFINDER_H_
#define _SUBSETFINDER_H_

#include "../NotchedBoard.h"

// Switch off using precomputed bitcount vs function
// Should only be used in sudoku namespace
#define BITCOUNT(x) \
	(bitcount::BitCountArray[x])

namespace sudoku
{
	template <int subsetSize, int UNIT>
	int FindNakedSubset(NotchedBoard& board)
	{
		CELL_INDEX cellIndex[subsetSize];
		BITMASK candidates[subsetSize];
		BITMASK combined;

		int indices[subsetSize];
		int useCount = 0;
		
		// Update the boards possibility matrix
		for(int i = 0; i < UNIT; i++)
			board.UpdateCellPossible(i);

		// For every group
		for(int g = 0; g < UNIT*3; g++)
		{
			// Reset the index array
			for(int i = 0; i < subsetSize; i++)
				indices[i] = i;

			// While the base index is below proper limit
			// eg last index of count 3 = {6, 7, 8}, check for 6
			while(indices[0] < (UNIT - subsetSize + 1))
			{
				combined = 0;
				for(int i = 0; i < subsetSize; i++)
				{
					cellIndex[i] = board.IterateGroups(g, indices[i]);
					candidates[i]  = board.GetCellPossible(cellIndex[i]);
					combined |= candidates[i];

					if(candidates[i] == 0)
					{
						combined = 0;
						break;
					}
				}

				// found naked subset
				if(BITCOUNT(combined) == subsetSize)
				{
					BITMASK mask = 0;
					for(int i = 0; i < UNIT; i++)
					{
						bool seen = false;

						CELL_INDEX x = board.IterateGroups(g, i);
						for(int j = 0; j < subsetSize; j++)
							if(x == cellIndex[j])
								seen = true;

						if(seen) continue;

						mask |= board.GetCellPossible(x) & combined;
						board.MaskCell(x, combined);
					}

					if(mask)
						useCount++;
				}
				
				// Do incrementing logic
				indices[subsetSize-1]++;
				for(int i = subsetSize - 1; i > 0; i--)
				{
					if(indices[i] >= (UNIT - subsetSize + i + 1))
					{
						indices[i-1]++;
						indices[i] = -1;
					}
				}

				for(int i = 1; i < subsetSize; i++)
					if(indices[i] == -1)
						indices[i] = indices[i-1]+1;
			}
		}
		return useCount;
	}
	
}

#endif