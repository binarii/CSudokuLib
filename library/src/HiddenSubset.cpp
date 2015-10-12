#include "technique/HiddenSubset.h"
#include "AbstractBoard.h"
#include "util.h"


namespace {
    using namespace sudoku;

    struct HelperData {
        const int size;
        Board &board;
        int counter;
        int group;
        int cells[4];
    };

    // Loop recursively to give proper depth
    template<int iter>
    void findHelper(HelperData &data, int lastCell, bitmask_t combined) {
        Board &board = data.board;
        const int iterNext = iter - 1;
        const int loopMax = board.UNIT - iterNext;

        bitmask_t candidates;
        for (int c = lastCell + 1; c < loopMax; c++) {
            data.cells[iterNext] = board.iterate(data.group, c);
            candidates = board.get_candidates(data.cells[iterNext]);
            findHelper<iterNext>(data, c, combined | candidates);
        }
    }

    // Once at the base case, see if we've accumulated cells of a naked subset
    template<>
    void findHelper<0>(HelperData &data, int lastCell, bitmask_t combined) {
        int cBitcount = util::bitcount_cached(combined);
        Board &board = data.board;

        if (cBitcount <= data.size) {
            return;
        }

        for (int i = 0; i < board.UNIT; i++) {
            cell_t pos = board.iterate(data.group, i);

            if (pos == data.cells[0] || pos == data.cells[1] || pos == data.cells[2] || pos == data.cells[3]) {
                continue;
            }

            combined &= ~board.get_candidates(pos);
        }

        if (util::bitcount_cached(combined) == data.size && cBitcount != data.size) {
            data.counter++;
            for (int i = 0; i < 4; i++) {
                if (data.cells[i] >= 0) {
                    board.mask(data.cells[i], ~combined);
                }
            }
        }
    }

    // Starting point for the finder, loop through all the units
    // and call the helper function
    template<int subsetSize>
    int find(Board &board) {
        HelperData data = {subsetSize, board, 0, 0, {-1, -1, -1, -1}};

        // Loop through all units
        for (data.group = 0; data.group < board.UNIT * 3; data.group++) {
            findHelper<subsetSize>(data, -1, 0);
        }

        return data.counter;
    }
}

namespace sudoku {
    int HiddenSingle::step(Board &board) {
        cell_t x;
        int useCount = 0;

        for (int u = 0; u < board.UNIT * 3; ++u) {
            bitmask_t once = 0;
            bitmask_t twice = 0;
            bitmask_t all = 0;

            for (int c1 = 0; c1 < board.UNIT; ++c1) {
                // Get the board position
                x = board.iterate(u, c1);

                // Get possible mask and value mask
                board.update_candidates(x);
                bitmask_t possible = board.get_candidates(x);
                bitmask_t boardVal = board.get_val(x);

                all |= (possible | boardVal);
                twice |= (once & possible);
                once |= possible;
            }

            once &= ~twice;

            if (!once) {
                continue;
            }

            // Find the hidden single
            once = util::get_lsb(once);
            for (int i = 0; i < board.UNIT; ++i) {
                x = board.iterate(u, i);
                if (board.get_candidates(x) & once) {
                    board.set(x, once);
                    useCount++;
                }
            }

        }
        return useCount;
    }

    int HiddenPair::step(Board &board) {
        return find<2>(board);
    }

    int HiddenTriple::step(Board &board) {
        return find<3>(board);
    }

    int HiddenQuad::step(Board &board) {
        return find<4>(board);
    }
}
