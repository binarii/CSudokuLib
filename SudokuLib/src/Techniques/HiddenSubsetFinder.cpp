#include "HiddenSubsetFinder.h"

#include "../BoardAbstract.h"
#include "../BitCount.h"

namespace sudoku
{	
	// Starting point for the finder, loop through all the units
	// and call the helper function
	template <int subsetSize>
	int HiddenSubsetFinder::find(Board& board) {
		const BITMASK combined =  0;
		const int     lastCell = -1;

		// Initialize defaults
		m_counter = 0;
		for(int i = 0; i < 4; i++) {
			m_cells[i] = -1;
		}

		// Loop through all units
		for(m_currentGroup = 0; m_currentGroup < board.UNIT * 3; m_currentGroup++) {
			findHelper<subsetSize>(board, subsetSize, lastCell, combined);
		}

		return m_counter;
	}

	// Loop recursively to give proper depth
	template <int iter>
	void HiddenSubsetFinder::findHelper(Board& board, const int size, int lastCell, BITMASK combined) {		
		const int iterNext = iter - 1;
		const int loopMax  = board.UNIT - iterNext;

		BITMASK candidates;		

		for(int c = lastCell + 1; c < loopMax; c++) {
			m_cells[iterNext] = board.iterate(m_currentGroup, c);
			candidates = board.getCandidates(m_cells[iterNext]);
			
			findHelper<iterNext>(board, size, c, combined | candidates);
		}
	}
	
	// Once at the base case, see if weve accumulated cells of a naked subset
	template <>
	void HiddenSubsetFinder::findHelper<0>(Board& board, const int size, int lastCell, BITMASK combined) {
		int cBitcount = bitcount::BitCountArray[combined];

		if(cBitcount <= size) {
			return;
		}

		for(int i = 0; i < board.UNIT; i++)
		{
			CELL_INDEX pos = board.iterate(m_currentGroup, i);
			if(pos == m_cells[0] || pos == m_cells[1] || 
			   pos == m_cells[2] || pos == m_cells[3])
				continue;

			combined &= ~board.getCandidates(pos);
		}

		if(bitcount::BitCountArray[combined] == size && cBitcount != size)
		{
			for(int i = 0; i < 4; i++) {
				if(m_cells[i] < board.GRID) {
					board.mask(m_cells[i], ~combined);
				}
			}
			m_counter++;
		}	
	}

	template int HiddenSubsetFinder::find<2>(Board& board);
	template int HiddenSubsetFinder::find<3>(Board& board);
	template int HiddenSubsetFinder::find<4>(Board& board);
}