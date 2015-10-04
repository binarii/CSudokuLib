#ifndef CSUDOKU_PUZZLEDIMENSIONS_H
#define CSUDOKU_PUZZLEDIMENSIONS_H

#include "sudoku_types.h"

namespace sudoku {
    template<int size>
    class Dimensions {
    public:
        static const int BOX = size;
        static const int UNIT = BOX * BOX;
        static const int GRID = UNIT * UNIT;
        static const bitmask_t MASK = ((1 << (UNIT + 1)) - 2);
    };
}

#endif //CSUDOKU_PUZZLEDIMENSIONS_H
