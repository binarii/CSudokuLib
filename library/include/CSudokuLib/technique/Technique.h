#ifndef CSUDOKU_TECHNIQUE_H
#define CSUDOKU_TECHNIQUE_H

#include "../prerequisites.h"

namespace sudoku {
    class Technique {
    public:
        virtual int step(Board &board) = 0;
    };
}

#endif //CSUDOKU_TECHNIQUE_H
