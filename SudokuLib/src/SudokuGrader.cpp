#include "SudokuGrader.h"
#include "BoardAbstract.h"

// techniques
#include "Techniques\NakedSingle.h"
#include "Techniques\HiddenSingle.h"
#include "Techniques\NakedPair.h"
#include "Techniques\NakedTriple.h"
#include "Techniques\HiddenPair.h"
#include "Techniques\HiddenTriple.h"
#include "Techniques\NakedQuad.h"

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
		
		technique = new HiddenPair();
		m_techniques.push_back(technique);
		
		technique = new HiddenTriple();
		m_techniques.push_back(technique);
		
		technique = new NakedQuad();
		m_techniques.push_back(technique);
	}

	Grader::~Grader()
	{
		for(unsigned int i = 0; i < m_techniques.size(); i++)
		{
			delete m_techniques[i];
		}

		m_techniques.clear();
	}

	bool Grader::Evaluate(BoardAbstract<3>& board)
	{
		// Start the clock
		m_timer.StartTimer();
		Reset();

		// Get board in a good state
		for(int i = 0; i < GRID; i++)
		{
			if(board.getValue(i) != 0)
				board.mask(i, board.MASK);
			board.updateCandidates(i);
		}

		int count = 1;

		while((count > 0) && (!board.isBoardFull()))
		{
			// Default cell updater
			for(int i = 0; i < 81; i++)
				board.updateCandidates(i);

			count = 0;
			for(unsigned int i = 0; i < m_techniques.size(); i++)
			{
				count = m_techniques[i]->step(board);
				if(count > 0)
					break;
			}
		}


		m_solveTime = m_timer.GetTime();
		return board.isBoardFull();
	}

	double Grader::GetSolveTime()
	{
		return m_solveTime;
	}

	int Grader::GetDifficulty()
	{
		int difficulty = 0;

		for(unsigned int i = 0; i < m_techniques.size(); i++)
			difficulty += m_techniques[i]->getCost() * m_techniques[i]->getCount();

		return difficulty;
	}
		
	int Grader::GetMaxTechnique()
	{
		int difficulty = 0;

		for(unsigned int i = 0; i < m_techniques.size(); i++)
			if(m_techniques[i]->getCount() > 0)
				difficulty = max(m_techniques[i]->getCost(), difficulty);

		return difficulty;
	}

	void Grader::Reset()
	{
		for(unsigned int i = 0; i < m_techniques.size(); i++)
			m_techniques[i]->resetCount();
	}
}