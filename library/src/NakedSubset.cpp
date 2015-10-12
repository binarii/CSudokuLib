#include "technique/NakedSubset.h"
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

            if (candidates == 0 || util::bitcount_cached(candidates | combined) > data.size) {
                continue;
            }

            findHelper<iterNext>(data, c, combined | candidates);
        }
    }

    // Once at the base case, see if we've accumulated cells of a naked subset
    template<>
    void findHelper<0>(HelperData &data, int lastCell, bitmask_t combined) {
        Board &board = data.board;

        // If we have accumulated correct number of candidates
        if (util::bitcount_cached(combined) == data.size) {
            bitmask_t mask = 0;
            for (int i = 0; i < board.UNIT; i++) {
                cell_t pos = board.iterate(data.group, i);

                // If it is not a cell part of the subset
                if (pos == data.cells[0] || pos == data.cells[1] || pos == data.cells[2] || pos == data.cells[3]) {
                    continue;
                }

                mask |= board.get_candidates(pos) & combined;
                board.mask(pos, combined);
            }

            if (mask) {
                data.counter++;
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
    int NakedSingle::step(Board &board) {
        int count;
        int useCount = 0;
        bitmask_t saveVal = 0;

        for (cell_t i = 0; i < board.GRID; ++i) {
            board.update_candidates(i);

            if (board.get_val(i) != 0)
                continue;

            bitmask_t possible = board.get_candidates(i);

            // Get the bit count for the cell
            count = util::bitcount_cached(possible);

            // If cell has one possibility play it
            if (count == 1) {
                // Play move and clear possible
                board.set(i, possible);
                useCount++;
            }
        }

        return useCount;
    }

    int NakedPair::step(Board &board) {
        return find<2>(board);
    }

    int NakedTriple::step(Board &board) {
        return find<3>(board);
    }

    int NakedQuad::step(Board &board) {
        return find<4>(board);
    }
}