#include "GradeInterface.h"

#include <SudokuBoard.h>
#include <SudokuGrader.h>
#include <Util.h>

#include <iomanip>
#include <fstream>

namespace 
{	
	sudoku::Board<3> board;
	sudoku::Grader grader;
}

int GradeSingle(CLI_Input& input, int index, double& timeAccum)
{	
	sudoku::util::LoadBoard(board, input.puzzle);

	bool solution = grader.Evaluate(board);
	double time = grader.GetSolveTime();
	int grade = solution ? grader.GetDifficulty() : -1;
	timeAccum += time;

	if(input.singleLine)
	{
		(*input.output) << std::setw(6)  << index << std::setw(12) << time 
			            << std::setw(14) << grade << std::endl;
	}
	else
	{
		(*input.output) << "Puzzle Index: " << index << std::endl;
		(*input.output) << "Solve Time:   " << time << std::endl;
		(*input.output) << "Difficulty:   " << grade << std::endl;
	}

	return grade;
}

void Grade(CLI_Input& input)
{
	if(input.singleLine)
	{
		(*input.output) << std::setw(6) << "Puzzle" << std::setw(12) << "Time" 
			            << std::setw(14) << "Difficulty" << std::endl;
	}

	if(input.puzzle != "")
	{
		double time = 0;
		GradeSingle(input, 1, time);
	}

	if(input.inputFile != "")
	{
		double time = 0.0;
		int solveCount = 0;
		int totalCount = 0;
		int totalGrade = 0;

		std::ifstream inputFile;

		inputFile.open(input.inputFile, std::ios::in);

		if(inputFile.is_open())
		{
			inputFile.seekg(0);
			while(std::getline(inputFile, input.puzzle) && input.puzzle.size() == 81)
			{
				totalCount++;
				int diff = GradeSingle(input, totalCount, time);
				solveCount += (diff != -1) ? 1 : 0;
				totalGrade += (diff != -1) ? diff : 0;
			}

			(*input.output) << std::endl;
			(*input.output) << "Finished Solving File." << std::endl;
			(*input.output) << "Total Solve Time: " << time << std::endl;
			(*input.output) << "Average Solve Time: " << time / (double)totalCount << std::endl;
			(*input.output) << "Solved: " << solveCount << "/" << totalCount << std::endl;
			if(solveCount > 0)
				(*input.output) << "Average Difficulty: " << totalGrade / solveCount << std::endl;
		}
		else
		{
			(*input.output) << "Error reading from file" << std::endl;
		}
	}
}