#ifndef CSUDOKU_TYPES_H
#define CSUDOKU_TYPES_H

namespace sudoku {
    // Denote the position of a cell
    typedef unsigned int cell_t;

    // Bitmask for cell value or tick marks
    typedef unsigned int bitmask_t;

    struct cell_ref_t {
        int row;
        int col;
        int box;
    };
}

#endif //CSUDOKU_TYPES_H
