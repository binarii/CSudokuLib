#include "AbstractBoard.h"
#include <string.h>

#define TMPL template <int size>
#define TCL AbstractBoard<size>

namespace sudoku {

    TMPL TCL::AbstractBoard() : Indexing<size>() {
        reset();
    }

    TMPL TCL::AbstractBoard(const sudoku::AbstractBoard<size> &other) : Indexing<size>() {
        copy(other);
    }

    TMPL TCL::~AbstractBoard() {

    }

    TMPL void TCL::reset() {
        setCount = 0;
        memset(&gameBoard, 0, sizeof(gameBoard));
        memset(&boardMask, 0, sizeof(boardMask));
        memset(&candidates, 0, sizeof(candidates));
        memset(&rowConflicts, 0, sizeof(rowConflicts));
        memset(&colConflicts, 0, sizeof(colConflicts));
        memset(&boxConflicts, 0, sizeof(boxConflicts));
    }

    TMPL void TCL::copy(const sudoku::AbstractBoard<size> &other) {
        setCount = other.setCount;
        memcpy(&gameBoard, &other.gameBoard, sizeof(gameBoard));
        memcpy(&boardMask, &other.boardMask, sizeof(boardMask));
        memcpy(&candidates, &other.candidates, sizeof(candidates));
        memcpy(&rowConflicts, &other.rowConflicts, sizeof(rowConflicts));
        memcpy(&colConflicts, &other.colConflicts, sizeof(colConflicts));
        memcpy(&boxConflicts, &other.boxConflicts, sizeof(boxConflicts));
    }

    TMPL bool TCL::is_valid() const {
        // Iterate all the units (27 standard)
        for (int i = 0; i < UNIT * 3; ++i) {
            bitmask_t once = 0;
            bitmask_t twice = 0;

            // Iterate each cell in the unit
            for (int j = 0; j < UNIT; ++j) {

                // Get the board position
                cell_t x = iterate(i, j);

                // Get possible mask and value mask
                bitmask_t boardVal = get_val(x);

                // Seen twice if current board val and seen once
                twice |= (once & boardVal);

                // Seen once if the current value
                once |= boardVal;
            }

            // Board invalid if any value seen twice
            if (twice) {
                return false;
            }
        }
        return true;
    }

    template
    class AbstractBoard<2>;

    template
    class AbstractBoard<3>;

    template
    class AbstractBoard<4>;

    template
    class AbstractBoard<5>;
}

#undef TMPL
#undef TCL
