#include "ParseCLI.h"

#include <iostream>
#include <fstream>

void ParseGeneration(std::vector<std::string> args, std::ofstream& file, GEN_Input& input)
{
	input.output = &std::cout;
	input.count = 10;
	input.genType = 0;
	input.printSolution = false;

	for(int i = 1; i < args.size(); i++)
	{
		if(args[i] == "-n")
		{
			if(i + 1 < args.size())
			{
				int n = atoi(args[++i].c_str());

				if(n > 0)
					input.count = n;
			}
		}
		else if(args[i] == "-t")
		{
			if(i + 1 < args.size())
			{
				int n = atoi(args[++i].c_str());

				if(n >= 0 && n <= 3)
					input.genType = n;
			}
		}
		else if(args[i] == "-o")
		{
			if(i + 1 < args.size())
			{
				file.open(args[++i], std::ios::out);
				if(!file.is_open())
					return;

				input.output = &file;
			}
		}
		else if(args[i] == "-print")
		{
			input.printSolution = true;
		}
	}
}

CLI_Input ParseCLI(std::vector<std::string> args, std::ofstream& file)
{
	CLI_Input input;
		
	// Defaults
	input.inputFile = "";
	input.puzzle = "";
	input.singleLine = false;
	input.printBoard = false;
	input.validCheck = false;
	input.inputLegal = true;
	input.output = &std::cout;

	// Read parameters
	for(int i = 1; i < args.size(); i++)
	{
		if(args[i] == "-f")
		{
			if(i + 1 < args.size())
				input.inputFile = args[++i]; 
		}
		else if(args[i] == "-p")
		{
			if(i + 1 < args.size())
			{
				input.puzzle = args[++i]; 
				if(input.puzzle.length() != 81)
				{
					input.inputLegal = false;
					return input;
				}
			}
		}
		else if(args[i] == "-o")
		{
			if(i + 1 < args.size())
			{
				file.open(args[++i], std::ios::out);
				if(!file.is_open())
				{
					input.inputLegal = false;
					return input;
				}
				input.output = &file;
			}
		}
		else if(args[i] == "-sl")
		{
			input.singleLine = true;
		}
		else if(args[i] == "-print")
		{
			input.printBoard = true;
		}
		else if(args[i] == "-valid")
		{
			input.validCheck = true;
		}
	}

	return input;
}