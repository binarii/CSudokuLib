#include "PuzzleFactory.h"

#include "BoardAbstract.h"
#include "ScrambleSolve.h"

// Include the various different minimizers
#include "MinimizeMethods\MinCorners.h"
#include "MinimizeMethods\MinDefault.h"
#include "MinimizeMethods\MinDiagonal.h"
#include "MinimizeMethods\MinHorizontal.h"
#include "MinimizeMethods\MinVertical.h"

#define TEMPLATE template <int size>
#define TCLASS PuzzleFactory<size>

namespace sudoku
{
	TEMPLATE
	TCLASS::PuzzleFactory() {
		m_minimizers = new MinMethod*[ST_TOTAL];

		for(int i = 0; i < ST_TOTAL; i++) {
			m_minimizers[i] = 0;
		}

		m_minimizers[ST_DEFAULT] = new MinDefault<size>();
		m_minimizers[ST_DIAGONAL] = new MinDiagonal<size>();
		m_minimizers[ST_VERTICAL] = new MinVertical<size>();
		m_minimizers[ST_HORIZONTAL] = new MinHorizontal<size>();
		m_minimizers[ST_CORNERS] = new MinCorners<size>();
	}

	TEMPLATE
	TCLASS::~PuzzleFactory() {
		if(m_minimizers) {
			for(int i = 0; i < ST_TOTAL; i++) {
				if(m_minimizers[i]) {
					delete m_minimizers[i];
					m_minimizers[i] = 0;
				}
			}

			delete [] m_minimizers;
			m_minimizers = 0;
		}
	}

	TEMPLATE
	double TCLASS::generate(BoardAbstract<size> board, SYMMETRY_TYPE symm, int minClues) {
		board.reset();

		ScrambleSolve<size> solver;

		solver.solve(board);

		return solver.getTime() + minimize(board, symm, minClues);
	}

	TEMPLATE
	double TCLASS::minimize(BoardAbstract<size> board, SYMMETRY_TYPE symm, int minClues) {
		MinMethod* minimizer = getMinimizer(symm);

		if(minimizer == NULL) {
			return 0.0;
		}

		minimizer->startTimer();
		minimizer->setMinClueCount(minClues);
		minimizer->minimize(board);
		minimizer->stopTimer();

		return minimizer->getTime();
	}

	TEMPLATE
	typename TCLASS::MinMethod* TCLASS::getMinimizer(SYMMETRY_TYPE symm) {
		return m_minimizers[(int)symm];
	}

	template class PuzzleFactory<2>;
	template class PuzzleFactory<3>;
	template class PuzzleFactory<4>;
	template class PuzzleFactory<5>;
}

#undef TEMPLATE
#undef TCLASS