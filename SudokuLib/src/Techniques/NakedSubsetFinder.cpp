#include "NakedSubsetFinder.h"

#include "../BoardAbstract.h"
#include "../BitCount.h"

namespace sudoku
{	
	// Starting point for the finder, loop through all the units
	// and call the helper function
	template <int subsetSize>
	int NakedSubsetFinder::find(Board& board) {
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
	void NakedSubsetFinder::findHelper(Board& board, const int size, int lastCell, BITMASK combined) {		
		const int iterNext = iter - 1;
		const int loopMax  = board.UNIT - iterNext;

		BITMASK candidates;		

		for(int c = lastCell + 1; c < loopMax; c++) {
			m_cells[iterNext] = board.iterate(m_currentGroup, c);
			candidates = board.getCandidates(m_cells[iterNext]);

			// Cant be a naked subset without candidates or if size is already too great
			if(candidates == 0 || bitcount::BitCountArray[candidates | combined] > size) {
				continue;
			}
			
			findHelper<iterNext>(board, size, c, combined | candidates);
		}
	}
	
	// Once at the base case, see if weve accumulated cells of a naked subset
	template <>
	void NakedSubsetFinder::findHelper<0>(Board& board, const int size, int lastCell, BITMASK combined) {
		// If we have accumulated correct number of candidates
		if(bitcount::BitCountArray[combined] == size) {
			BITMASK mask = 0;
			for(int i = 0; i < board.UNIT; i++) {
				CELL_INDEX pos = board.iterate(m_currentGroup, i);
				
				// If it is not a cell part of the subset
				if(pos == m_cells[0] || pos == m_cells[1] || pos == m_cells[2] || pos == m_cells[3]) {
					continue;
				}
				
				mask |= board.getCandidates(pos) & combined;
				board.mask(pos, combined);
			}
			
			if(mask) {
				m_counter++;
			}  
		}
	}

	template int NakedSubsetFinder::find<2>(Board& board);
	template int NakedSubsetFinder::find<3>(Board& board);
	template int NakedSubsetFinder::find<4>(Board& board);
}