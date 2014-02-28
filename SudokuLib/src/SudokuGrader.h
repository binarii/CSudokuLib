#ifndef _SUDOKUGRADER_H_
#define _SUDOKUGRADER_H_

#include "Types.h"
#include "Timer.h"

#include <vector>

namespace sudoku
{
	// Forward the board class
	template <int boxSize>
	class Board;

	class Technique;

	class Grader
	{
	public:
		Grader();
		~Grader();

		bool Evaluate(Board<3>& board);

		double GetSolveTime();
		int GetDifficulty();

	private:
		void Reset();

	private:
		std::vector<Technique*> m_techniques;

		double m_solveTime;
		Timer m_timer;
	};
}

#endif