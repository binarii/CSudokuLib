#ifndef _SUDOKUGRADER_H_
#define _SUDOKUGRADER_H_

#include "Types.h"
#include "Timer.h"
#include "SudokuPrerequisites.h"

#include <vector>

namespace sudoku
{

	class Grader
	{
	public:
		Grader();
		~Grader();

		bool Evaluate(BoardAbstract<3>& board);

		double GetSolveTime();
		int GetDifficulty();
		int GetMaxTechnique();

	private:
		void Reset();

	private:
		std::vector<Technique*> m_techniques;

		double m_solveTime;
		Timer m_timer;
	};
}

#endif