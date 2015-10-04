#ifndef CSUDOKU_SOLVEMETHOD_H
#define CSUDOKU_SOLVEMETHOD_H

#include "prerequisites.h"

namespace sudoku {
    template<int size>
    class SolveMethod {
    public:
        virtual int solve(AbstractBoard <size> &board) = 0;
    };
}

#endif //CSUDOKU_SOLVEMETHOD_H
