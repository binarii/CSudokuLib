#include "ScrambleSolve.h"
#include "AbstractBoard.h"
#include "util.h"

#define TMPL template <int size>
#define TCL ScrambleSolve<size>

namespace sudoku {
    TMPL TCL::ScrambleSolve() {
    }

    TMPL TCL::~ScrambleSolve() {
    }

    TMPL int TCL::solve(AbstractBoard<size> &board) {
        return backtrackSolve(board);
    }

    TMPL int TCL::backtrackSolve(AbstractBoard<size> &board) {
        const int UNIT = this->UNIT;
        if (board.is_full()) {
            return 1;
        }

        // Choose the cells linearly
        cell_t pos = (cell_t) board.get_filled_count();

        // Get the candidates
        board.update_candidates(pos);
        bitmask_t possible = board.get_candidates(pos);

        // Get the order we will chose in
        bitmask_t cellOrder[UNIT];
        for (int i = 0; i < UNIT; i++) {
            cellOrder[i] = (cell_t) (1 << (i + 1));
        }

        // Shuffle the choosing order
        util::shuffle_array(cellOrder, UNIT);

        // Try the values and recurse
        for (int i = 0; i < UNIT; i++) {
            if (cellOrder[i] & possible) {
                auto cellValue = cellOrder[i];
                board.set(pos, cellValue);
                auto found = backtrackSolve(board);

                if (found > 0) {
                    return found;
                }

                board.remove(pos);
                possible &= ~cellValue;
            }
        }

        return 0;
    }


    template
    class ScrambleSolve<2>;

    template
    class ScrambleSolve<3>;

    template
    class ScrambleSolve<4>;

    template
    class ScrambleSolve<5>;
}

#undef TMPL
#undef TCL
