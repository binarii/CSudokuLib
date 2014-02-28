#include "GradeInterface.h"
#include "SolveInterface.h"
#include "GenerationInterface.h"
#include "ParseCLI.h"

#include <BitCount.h>
#include <Util.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#pragma comment(lib, "SudokuLib.lib")

int main(int argc, char** stringArgs)
{
	sudoku::bitcount::Initialize();
	sudoku::util::Initialize();

	std::vector<std::string> args;
	std::ofstream file;

	for(int i = 1; i < argc; i++)
		args.push_back(std::string(stringArgs[i]));

	/**
	args.push_back("generate");
	args.push_back("-o");
	args.push_back("gen.txt");
	args.push_back("-n");
	args.push_back("100");
	//args.push_back("-p");
	//args.push_back("409716000610389040070245169000964021004173690196852030960421070030698000040537906");
	//args.push_back("-o");
	//args.push_back("stats.txt");
	//*/


	if(args.size() < 1)
		return 0;


	if(args[0] == "generate")
	{
		GEN_Input input;
		ParseGeneration(args, file, input);

		Generate(input);
	}
	else if(args[0] == "solve" || args[0] == "grade")
	{
		CLI_Input input;
		input = ParseCLI(args, file);
		if(!input.inputLegal)
		{
			std::cout << "Error parsing input" << std::endl;
			return 0;
		}

		if(args[0] == "solve")
		{
			Solve(input);
		}

		if(args[0] == "grade")
		{
			Grade(input);
		}
	}
	else
	{
		std::cout << "Incorrect parameters" << std::endl;
	}


	file.close();
	return 0;
}