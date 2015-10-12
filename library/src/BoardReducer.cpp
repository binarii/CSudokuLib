#include "BoardReducer.h"
#include "AbstractBoard.h"
#include "QuickSolve.h"

#define TMPL template <int size>
#define TCL BoardReducer<size>

namespace {
    using namespace sudoku;

    template<int size>
    inline bool remove_from_board(AbstractBoard<size> &board, const std::vector<cell_t> &cells) {
        bool result = false;
        for (auto j : cells) {
            if (!board.is_cell_empty(j)) {
                board.remove(j);
                result = true;
            }
        }
        return result;
    }
}

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
        QuickSolve<size> solver(1);
        AbstractBoard<size> boardCopy(board);

        for (auto cellsToDig : order) {
            if (board.get_filled_count() <= targetCount) {
                break;
            }

            // Recopy the board
            boardCopy.copy(board);

            // Dig out cells in copy
            remove_from_board(boardCopy, cellsToDig);

            bool unique = true;
            for (auto j : cellsToDig) {
                // Observe that if the solution is not unique, then an alternate solution will
                // have a different value in place of one of the values we removed. Thus, we
                // can mask each one sequentially, and see if one of the values, when removed
                // as a possibility from the solution still gives a solved board.
                auto mask = board.get_val(j);

                boardCopy.mask(j, mask);
                solutionCount = solver.solve(boardCopy);
                if (solutionCount == 1) {
                    unique = false;
                    break;
                } else {
                    boardCopy.clear_mask(j);
                }
            }

            if (unique) {
                remove_from_board(board, cellsToDig);
            }
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