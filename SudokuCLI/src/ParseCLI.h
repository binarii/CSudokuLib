#ifndef _PARSECLI_H_
#define _PARSECLI_H_

#include <string>
#include <ostream>
#include <vector>

struct CLI_Input
{
	std::string inputFile;
	std::string puzzle;
	std::ostream* output;
	bool singleLine;
	bool printBoard;
	bool validCheck;

	bool inputLegal;
};

struct GEN_Input
{
	std::ostream* output;
	int count;
	int genType;
	bool printSolution;
};

void ParseGeneration(std::vector<std::string> args, std::ofstream& file, GEN_Input& input);

CLI_Input ParseCLI(std::vector<std::string> args, std::ofstream& file);


#endif