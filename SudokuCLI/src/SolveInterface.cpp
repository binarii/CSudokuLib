#include "SolveInterface.h"

#include <Sudoku.h>

#include <iomanip>
#include <fstream>

namespace
{	
	sudoku::Board board;
	sudoku::Board boardCopy;
	sudoku::QuickSolve<3> solver;
}


bool SolveSingle(CLI_Input& input, int index, double& timeAccum)
{

	if(input.validCheck)
		solver.setMaxSolutionCount(2);

	sudoku::util::LoadBoard(board, input.puzzle);
	boardCopy.copy(board);

	int solutions = solver.solve(board);
	double time = solver.getTime();
	timeAccum += time;

	if(input.singleLine)
	{
		(*input.output) << std::setw(6) << index << std::setw(12) << time 
			            << std::setw(14) << solutions << std::endl;
	}
	else
	{
		(*input.output) << "Puzzle Index: " << index << std::endl;
		(*input.output) << "Solve Time:   " << time << std::endl;
		(*input.output) << "Solutions:    " << solutions << std::endl;
	}

	if(input.printBoard && !input.singleLine)
	{
		sudoku::util::PrintBoard(boardCopy, (*input.output));
		sudoku::util::PrintBoard(board,     (*input.output));
	}
	else if(input.printBoard && input.singleLine)
	{
		(*input.output) << sudoku::util::GetBoardString(boardCopy) << "\t";
		(*input.output) << sudoku::util::GetBoardString(board) << std::endl;
	}

	return solutions > 0;
}

void Solve(CLI_Input& input)
{
	if(input.singleLine)
	{
		(*input.output) << std::setw(6) << "Puzzle" << std::setw(12) << "Time" 
			            << std::setw(14) << "Results" << std::endl;
	}

	if(input.puzzle != "")
	{
		double time = 0;
		SolveSingle(input, 1, time);
	}

	if(input.inputFile != "")
	{
		double time = 0.0;
		int solveCount = 0;
		int totalCount = 0;

		std::ifstream inputFile;

		inputFile.open(input.inputFile, std::ios::in);

		if(inputFile.is_open())
		{
			inputFile.seekg(0);
			while(std::getline(inputFile, input.puzzle) && input.puzzle.size() == 81)
			{
				totalCount++;
				solveCount += SolveSingle(input, totalCount, time) ? 1 : 0;
			}
		}

		(*input.output) << std::endl;
		(*input.output) << "Finished Solving File." << std::endl;
		(*input.output) << "Total Solve Time: " << time << std::endl;
		(*input.output) << "Average Solve Time: " << time / (double)totalCount << std::endl;
		(*input.output) << "Solved: " << solveCount << "/" << totalCount << std::endl;
	}
}