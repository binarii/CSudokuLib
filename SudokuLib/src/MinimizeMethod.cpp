#include "MinimizeMethod.h"

#include "QuickSolve.h"
#include "BoardAbstract.h"

#define TEMPLATE template <int size>
#define TCLASS MinimizeMethod<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::MinimizeMethod() {
		m_solveTime = 0.0;
		m_minClueCount = 0;
	}
	
	TEMPLATE
	TCLASS::~MinimizeMethod() {

	}
	
	TEMPLATE
	void TCLASS::startTimer() { 
		m_timer.StartTimer(); 
	}
	
	TEMPLATE
	void TCLASS::stopTimer()  { 
		m_solveTime = m_timer.GetTime(); 
	}
	
	TEMPLATE
	double TCLASS::getTime()  { 
		return m_solveTime; 
	}	
	
	TEMPLATE
	void TCLASS::setMinClueCount(int count) { 
		m_minClueCount = count; 
	}
	
	TEMPLATE
	void TCLASS::minimizePattern
			(BoardAbstract<size>& board, CELL_INDEX* digArray, int n, int rate) {

		int solutionCount;
		QuickSolve<size> solver;
		BoardAbstract<size> boardCpy(board);

		solver.SetMaxSolutionCount(2);

		for(int i = 0; (i < n) && (board.getFilledCount() > m_minClueCount); i++) {
			// Make a copy of the board
			boardCpy.copy(board);


			// Dig the cells for this 'round'
			for(int j = 0; j < rate; j++) {
				if(boardCpy.getValue(digArray[i*rate + j]) != 0) {
					boardCpy.remove(digArray[i*rate + j]);
				}
			}


			// Check if it is still unique
			solutionCount = solver.Solve(boardCpy);


			// If it is unique
			if(solutionCount == 1) {
				// Then we can dig cells on the real board
				for(int j = 0; j < rate; j++) {
					if(board.getValue(digArray[i*rate + j]) != 0) {
						board.remove(digArray[i*rate + j]);
					}
				}
			}
		}
	}

	template class MinimizeMethod<2>;
	template class MinimizeMethod<3>;
	template class MinimizeMethod<4>;
	template class MinimizeMethod<5>;
}

#undef TEMPLATE
#undef TCLASS