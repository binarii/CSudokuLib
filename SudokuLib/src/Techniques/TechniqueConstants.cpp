#include "TechniqueConstants.h"


const char* StrategyName[ST_TOTAL] = 
{
	"Naked Single",
	"Hidden Single",
	"Naked Pair",
	"Naked Triple",
	"Hidden Pair",
	"Hidden Tripple"
};

const int StrategyWeight[ST_TOTAL] = 
{
	1,
	1,
	5,
	5,
	15,
	15,
};