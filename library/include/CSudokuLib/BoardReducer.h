#ifndef CSUDOKU_BOARDREDUCER_H
#define CSUDOKU_BOARDREDUCER_H

#include <vector>
#include "prerequisites.h"
#include "CellChooser.h"

namespace sudoku {
    template<int size>
    class BoardReducer {
    public:
        BoardReducer(int targetCount);
        BoardReducer(CellChooser<size> *picker, int targetCount);
        ~BoardReducer();

        bool reduce_board(AbstractBoard<size> &board);

    private:
        int targetCount;
        std::vector<std::vector<cell_t>> order;
    };
}

#endif //CSUDOKU_BOARDREDUCER_H
