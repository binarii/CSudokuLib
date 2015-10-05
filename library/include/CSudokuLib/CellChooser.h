#ifndef CSUDOKU_CELLCHOOSER_H
#define CSUDOKU_CELLCHOOSER_H

#include <vector>
#include "prerequisites.h"
#include "AbstractBoard.h"

namespace sudoku {
    template<int size>
    class CellChooser {
    public:
        virtual const std::vector<std::vector<cell_t>> &pickCells() = 0;
    };
}

#endif //CSUDOKU_CELLCHOOSER_H
