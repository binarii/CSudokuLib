#ifndef _SUDOKUGRADER_H_
#define _SUDOKUGRADER_H_

#include "Timer.h"
#include "SudokuPrerequisites.h"

#include <vector>
#include <ostream>

namespace sudoku
{
	class Grader {
	public:
		Grader();
		~Grader();

		bool evaluate(Board& board);
		void printAnalysis(std::ostream& out);

		double getEvalTime();
		int getDifficulty();
		int getTechniqueLevel();

	private:
		void reset();

	private:
		std::vector<Technique*> m_techniques;

		double m_solveTime;
		Timer m_timer;
	};
}

#endif