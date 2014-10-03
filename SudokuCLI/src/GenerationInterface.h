#ifndef _GENERATIONINTERFACE_H_
#define _GENERATIONINTERFACE_H_

#include <ostream>

#include "ParseCLI.h"

int GenerateSingle(GEN_Input& input, double& timeAccum);
void Generate(GEN_Input& input);


#endif