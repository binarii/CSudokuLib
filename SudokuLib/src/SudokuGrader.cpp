#include "SudokuGrader.h"
#include "SudokuBoard.h"
#include "NotchedBoard.h"

// techniques
#include "Techniques\NakedSingle.h"
#include "Techniques\HiddenSingle.h"
#include "Techniques\NakedPair.h"
#include "Techniques\NakedTriple.h"

#define GRID 81
#define UNIT 9
#define BOX 3

namespace sudoku
{	
	Grader::Grader()
	{
		Technique* technique;

		technique = new NakedSingle();
		m_techniques.push_back(technique);

		technique = new HiddenSingle();
		m_techniques.push_back(technique);

		technique = new NakedPair();
		m_techniques.push_back(technique);
		
		technique = new NakedTriple();
		m_techniques.push_back(technique);
	}

	Grader::~Grader()
	{
		for(int i = 0; i < m_techniques.size(); i++)
		{
			delete m_techniques[i];
		}

		m_techniques.clear();
	}

	bool Grader::Evaluate(Board<3>& board)
	{
		// Start the clock
		m_timer.StartTimer();
		Reset();

		NotchedBoard copy(board);

		// Get board in a good state
		for(int i = 0; i < GRID; i++)
		{
			copy.UpdateCellPossible(i);
			if(copy.GetCellValue(i) != 0)
				copy.IgnoreCellPossible(i);
		}

		int count = 1;

		while((count > 0) && (copy.GetSetCount() != 81))
		{
			count = 0;
			for(int i = 0; i < m_techniques.size(); i++)
			{
				count = m_techniques[i]->Step(copy);
				if(count > 0)
					break;
			}
		}


		m_solveTime = m_timer.GetTime();
		return copy.GetSetCount() == GRID;
	}

	double Grader::GetSolveTime()
	{
		return m_solveTime;
	}

	int Grader::GetDifficulty()
	{
		int difficulty = 0;

		for(int i = 0; i < m_techniques.size(); i++)
			difficulty += m_techniques[i]->GetCost() * m_techniques[i]->GetCount();

		return difficulty;
	}

	void Grader::Reset()
	{
		for(int i = 0; i < m_techniques.size(); i++)
			m_techniques[i]->ResetCount();
	}
}