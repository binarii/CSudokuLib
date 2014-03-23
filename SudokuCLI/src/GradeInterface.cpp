#include "GradeInterface.h"

#include <Sudoku.h>

#include <iomanip>
#include <fstream>

namespace 
{	
	sudoku::Board board;
	sudoku::Grader grader;
}

int GradeSingle(CLI_Input& input, int index, double& timeAccum)
{	
	sudoku::util::LoadBoard(board, input.puzzle);
	sudoku::Board boardCopy(board);

	bool solution = grader.evaluate(board);
	double time = grader.getEvalTime();
	int difficulty = solution ? grader.getDifficulty() : -1;
	int grade = grader.getTechniqueLevel();
	timeAccum += time;

	if(input.singleLine)
	{
		(*input.output) << std::setw(6)  << index << std::setw(12) << time 
			            << std::setw(14) << difficulty 
						<< std::setw(12) << grade << std::endl;
		if(input.printBoard)
		{
			(*input.output) << sudoku::util::GetBoardString(boardCopy) << "\t";
			(*input.output) << sudoku::util::GetBoardString(board) << std::endl;
		}
	}
	else
	{
		(*input.output) << "Puzzle Index: " << index << std::endl;
		(*input.output) << "Solve Time:   " << time << std::endl;
		(*input.output) << "Difficulty:   " << difficulty << std::endl;
	}

	return difficulty;
}

void Grade(CLI_Input& input)
{
	if(input.singleLine)
	{
		(*input.output) << std::setw(6) << "Puzzle" << std::setw(12) << "Time" 
			            << std::setw(14) << "Difficulty" 
						<< std::setw(12) << "Grade" << std::endl;
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