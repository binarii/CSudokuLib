#include "GenerationInterface.h"

#include <Sudoku.h>
#include <string>

namespace
{
	sudoku::Board board;
	sudoku::PuzzleFactory<3> factory;
	sudoku::QuickSolve<3> solver;
}

int GenerateSingle(GEN_Input& input, double& timeAccum)
{
	board.reset();

	double time = factory.generate(board, (sudoku::SYMMETRY_TYPE) input.genType);

	int clueCount = board.getFilledCount();
	double solveTime = time;
	timeAccum += solveTime;

	(*input.output) << sudoku::util::GetBoardString(board);
	if(input.printSolution)
	{
		solver.solve(board);
		(*input.output) << "\t" << sudoku::util::GetBoardString(board);
	}
	(*input.output) << std::endl;


	return clueCount;
}

void Generate(GEN_Input& input)
{
	double solveTimeAccum = 0.0;
	int clueCountAccum = 0;

	for(int i = 0; i < input.count; i++)
	{
		clueCountAccum += GenerateSingle(input, solveTimeAccum);
	}

	(*input.output) << std::endl;
	(*input.output) << "Average clue count: " << (clueCountAccum) / (double)input.count << std::endl;
	(*input.output) << "Total time: " << solveTimeAccum << "ms" << std::endl;
}
