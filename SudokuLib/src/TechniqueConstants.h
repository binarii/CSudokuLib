#ifndef _TECHNIQUECONSTANTS_H_
#define _TECHNIQUECONSTANTS_H_

enum STRAT_TYPE
{
	ST_NAKED_SINGLE,
	ST_HIDDEN_SINGLE,
	ST_NAKED_PAIR,
	ST_NAKED_TRIPLE,
	ST_TOTAL,
};

extern const char* StrategyName[ST_TOTAL];
extern const int StrategyWeight[ST_TOTAL];

#endif