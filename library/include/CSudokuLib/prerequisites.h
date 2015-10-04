#ifndef CSUDOKU_PREREQUISITES_H
#define CSUDOKU_PREREQUISITES_H

#include "sudoku_types.h"

namespace sudoku {

    template<int size>
    class AbstractBoard;

    template<int size>
    class SolveMethod;

    typedef AbstractBoard<3> Board;
}

#endif //CSUDOKU_PREREQUISITES_H
