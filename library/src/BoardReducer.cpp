#include "BoardReducer.h"
#include "AbstractBoard.h"
#include "QuickSolve.h"

#define TMPL template <int size>
#define TCL BoardReducer<size>

namespace sudoku {
    TMPL TCL::BoardReducer(int targetCount) {
        this->targetCount = targetCount;
        for (cell_t i = 0; i < Dimensions<size>::GRID; i++) {
            order.push_back({i});
        }
    }

    TMPL TCL::BoardReducer(CellChooser<size> *picker, int targetCount) {
        this->targetCount = targetCount;
        this->order = picker->pickCells();
    }

    TMPL TCL::~BoardReducer() {

    }

    TMPL
    bool TCL::reduce_board(AbstractBoard<size> &board) {
        int solutionCount;
        QuickSolve<size> solver(2);
        AbstractBoard<size> boardCopy(board);

        for (auto cellsToDig : order) {
            if (board.get_filled_count() <= targetCount) {
                break;
            }

            // Dig out cells in copy
            for (auto j : cellsToDig) {
                if (!boardCopy.is_cell_empty(j)) {
                    boardCopy.remove(j);
                }
            }

            // Check if copy is still unique
            solutionCount = solver.solve(boardCopy);

            // If so, remove cells in original
            if (solutionCount == 1) {
                for (auto j : cellsToDig) {
                    if (!board.is_cell_empty(j)) {
                        board.remove(j);
                    }
                }
            }

            // Recopy the board
            boardCopy.copy(board);
        }

        return board.get_filled_count() <= targetCount;
    }

    template
    class BoardReducer<2>;

    template
    class BoardReducer<3>;

    template
    class BoardReducer<4>;

    template
    class BoardReducer<5>;
}

#undef TMPL
#undef TCL