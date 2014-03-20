#include "SudokuGrader.h"
#include "BoardAbstract.h"

#include <iomanip>

// techniques
#include "Techniques\NakedSingle.h"
#include "Techniques\HiddenSingle.h"
#include "Techniques\NakedPair.h"
#include "Techniques\NakedTriple.h"
#include "Techniques\HiddenPair.h"
#include "Techniques\HiddenTriple.h"
#include "Techniques\NakedQuad.h"

namespace sudoku
{	
	Grader::Grader() {
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

	Grader::~Grader() {
		for(unsigned int i = 0; i < m_techniques.size(); i++) {
			delete m_techniques[i];
		}

		m_techniques.clear();
	}

	bool Grader::evaluate(Board& board) {
		// Start the clock
		m_timer.StartTimer();
		reset();

		// Get board in a good state
		for(int i = 0; i < board.GRID; i++) {
			board.updateCandidates(i);
		}

		int count = 1;

		while((count > 0) && (!board.isBoardFull())) {

			// Default cell updater
			for(int i = 0; i < board.GRID; i++) {
				board.updateCandidates(i);
			}

			count = 0;
			for(unsigned int i = 0; i < m_techniques.size(); i++) {
				count = m_techniques[i]->step(board);
				if(count > 0) {
					break;
				}
			}
		}


		m_solveTime = m_timer.GetTime();
		return board.isBoardFull();
	}

	void Grader::printAnalysis(std::ostream& out) {
		out << std::endl;

		out << std::setw(30) << "Technique";
		out << std::setw(10) << "Cost";
		out << std::setw(10) << "Count";
		out << std::setw(15) << "Total Cost";
		out << std::endl;

		int totalDifficulty = 0;
		for(unsigned int i = 0; i < m_techniques.size(); i++) {
			int cost = m_techniques[i]->getCost();
			int count = m_techniques[i]->getCount();
			const char* name = m_techniques[i]->getName();

			int difficultyCost = cost * count;
			totalDifficulty += difficultyCost;

			out << std::setw(30) << name;
			out << std::setw(10) << cost;
			out << std::setw(10) << count;
			out << std::setw(15) << difficultyCost;
			out << std::endl;
		}

		out << std::setw(30+10+10+15) << totalDifficulty;
		out << std::endl;
	}

	double Grader::getEvalTime() {
		return m_solveTime;
	}

	int Grader::getDifficulty() {
		int difficulty = 0;

		for(unsigned int i = 0; i < m_techniques.size(); i++) {
			difficulty += m_techniques[i]->getCost() * m_techniques[i]->getCount();
		}

		return difficulty;
	}
		
	int Grader::getTechniqueLevel() {
		int difficulty = 0;

		for(unsigned int i = 0; i < m_techniques.size(); i++) {
			if(m_techniques[i]->getCount() > 0) {
				difficulty = max(m_techniques[i]->getCost(), difficulty);
			}
		}

		return difficulty;
	}

	void Grader::reset()
	{
		for(unsigned int i = 0; i < m_techniques.size(); i++) {
			m_techniques[i]->resetCount();
		}
	}
}