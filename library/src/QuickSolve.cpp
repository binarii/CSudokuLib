#include <limits.h>
#include "util.h"
#include "AbstractBoard.h"
#include "QuickSolve.h"

using sudoku::util::get_lsb;

#define TMPL template <int size>
#define TCL QuickSolve<size>

#define BITCOUNT(x) \
    ((BOX < 4) ? sudoku::util::bitcount_cached(x) : sudoku::util::bitcount(x))

namespace sudoku {
    TMPL TCL::QuickSolve() {
        maxSolnCount = 1;
    }

    TMPL TCL::~QuickSolve() {

    }

    TMPL int TCL::solve(AbstractBoard<size> &board) {
        return backtrack_solve(board);
    }

    TMPL void TCL::set_max_soln_count(int count) {
        maxSolnCount = count;
    }

    TMPL int TCL::backtrack_solve(AbstractBoard<size> &board) {
        if (board.is_full()) return 1;

        bitmask_t val = 0;
        cell_t pos = INT_MAX;
        int solutionsFound = 0;
        int count = find_single(board, pos, val);

        if (count == 0) {
            return 0;
        }

        for (bitmask_t i = get_lsb(val); val; i = get_lsb(val)) {
            board.set(pos, i);
            solutionsFound += backtrack_solve(board);

            if (solutionsFound >= maxSolnCount) {
                return solutionsFound;
            }

            board.remove(pos);
            val &= ~i;
        }

        return solutionsFound;
    }

    TMPL int TCL::find_single(AbstractBoard<size> &board, cell_t &pos, bitmask_t &value) {
        int count;
        int savePos = -1;
        int saveCount = UNIT + 1;

        cell_t i, j, x;
        bitmask_t saveVal = 0;

        for (i = 0; i < GRID; ++i) {
            // Refresh possible values for the duration of this function
            board.update_candidates(i);

            // Skip if filled in
            if (board.get_val(i) != 0) {
                continue;
            }

            bitmask_t possible = board.get_candidates(i);
            count = BITCOUNT(possible);

            if (count == 0) {
                return 0;
            } else if (count == 1) {
                pos = i;
                value = possible;
                return 1;
            } else if (count < saveCount) {
                savePos = i;
                saveVal = possible;
                saveCount = count;
            }
        }

        for (i = 0; i < UNIT * 3; ++i) {
            bitmask_t once = 0;
            bitmask_t twice = 0;
            bitmask_t all = 0;

            for (j = 0; j < UNIT; ++j) {
                x = iterate(i, j);

                bitmask_t possible = board.get_candidates(x);
                bitmask_t boardVal = board.get_val(x);

                all |= (possible | boardVal);
                twice |= (once & possible);
                once |= possible;
            }

            if (all != MASK) {
                return 0;
            }

            once &= ~twice;

            if (!once) {
                continue;
            }

            once = get_lsb(once);
            for (j = 0; j < UNIT; ++j) {
                pos = iterate(i, j);
                if (board.get_candidates(pos) & once) {
                    value = once;
                    return 1;
                }
            }
        }

        pos = savePos;
        value = saveVal;
        return (saveCount > UNIT) ? 0 : saveCount;
    }

    template
    class QuickSolve<2>;

    template
    class QuickSolve<3>;

    template
    class QuickSolve<4>;

    template
    class QuickSolve<5>;
}

#undef TMPL
#undef TCL
