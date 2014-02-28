#include "GenerationInterface.h"

#include <SudokuBoard.h>
#include <MinimizeBoard.h>
#include <ScrambleSolve.h>
#include <Util.h>

#include <string>

//
//void TestGenerator(int testCount)
//{
//	sudoku::Board<3> board;
//	sudoku::ScrambleSolve<3> scramble;
//	sudoku::MinimizeBoard<3> minimizer;
//	sudoku::QuickSolve<3> solver;
//
//	std::ofstream outputFile;
//	outputFile.open("genstats.txt", std::ios::out);
//
//	double solveTimeAccum = 0.0;
//	double clueCountAccum = 0.0;
//
//	for(int i = 0; i < testCount; i++)
//	{
//		board.Reset();
//
//		scramble.solve(board);
//		minimizer.Minimize(board, sudoku::MT_HORIZONTAL);
//
//		PrintBoard(board, std::cout);
//
//		int clueCount = board.GetSetCount();
//		double solveTime = scramble.GetSolveTime() + minimizer.GetSolveTime();
//		clueCountAccum += (double)clueCount;
//		solveTimeAccum += solveTime;
//
//		solver.Solve(board);
//
//		outputFile << clueCount << "\t" << solveTime << "\t" << solver.GetSolveTime() << std::endl;
//	}
//
//	outputFile << std::endl << std::endl;
//	outputFile << "Total solve time: " << solveTimeAccum << std::endl;
//	outputFile << "Average time:   " << (solveTimeAccum / (double)testCount) << std::endl;
//	outputFile << "Gen per second: " << (1000.0 * (double)testCount) / solveTimeAccum << std::endl;
//	outputFile << "Average clues:  " << clueCountAccum / (double)testCount << std::endl;
//}

namespace
{
	sudoku::Board<3> board;
	sudoku::MinimizeBoard<3> minimizer;
	sudoku::ScrambleSolve<3> scrambler;
}

int GenerateSingle(GEN_Input& input, double& timeAccum)
{
	board.Reset();

	scrambler.solve(board);
	minimizer.Minimize(board, sudoku::MT_NONE);

	int clueCount = board.GetSetCount();
	double solveTime = scrambler.GetSolveTime() + minimizer.GetSolveTime();
	timeAccum += solveTime;

	(*input.output) << sudoku::util::GetBoardString(board) << std::endl;

	return clueCount;
}

void Generate(GEN_Input& input)
{
	double solveTimeAccum = 0.0;
	int clueCountAccum = 0.0;

	for(int i = 0; i < input.count; i++)
	{
		clueCountAccum += GenerateSingle(input, solveTimeAccum);
	}

	(*input.output) << std::endl;
	(*input.output) << "Average clue count: " << (clueCountAccum) / (double)input.count << std::endl;
	(*input.output) << "Total time: " << solveTimeAccum << "ms" << std::endl;
}
