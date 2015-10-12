#ifndef CSUDOKU_BOARDABSTRACT_H
#define CSUDOKU_BOARDABSTRACT_H

#include "Indexing.h"

namespace sudoku {
    template<int size>
    class AbstractBoard : public Indexing<size> {

    public:
        AbstractBoard();
        AbstractBoard(const AbstractBoard<size> &other);
        ~AbstractBoard();

        void reset();
        void copy(const AbstractBoard<size> &other);

    public:
        void remove(cell_t cell);
        void mask(cell_t cell, bitmask_t mask);
        void set(cell_t cell, bitmask_t value);

        void clear_mask(cell_t cell);
        void update_candidates(cell_t cell);

        bitmask_t get_val(int row, int col) const;
        bitmask_t get_val(cell_t cell) const;
        bitmask_t get_candidates(cell_t cell) const;

        bool is_full() const;
        bool is_valid() const;
        bool is_solved() const;
        int get_filled_count() const;
        bool is_cell_empty(cell_t cell) const;

    public: // Make sure we can see imported symbols
        using Indexing<size>::BOX;
        using Indexing<size>::UNIT;
        using Indexing<size>::GRID;
        using Indexing<size>::MASK;
        using Indexing<size>::ref_for;
        using Indexing<size>::iterate;

    private:
        int setCount;
        bitmask_t gameBoard[GRID];
        bitmask_t boardMask[GRID];

        bitmask_t candidates[GRID];
        bitmask_t rowConflicts[UNIT];
        bitmask_t colConflicts[UNIT];
        bitmask_t boxConflicts[UNIT];
    };


    //---------------------------------------------------------------------------------------------
    // Begin Class Definitions
    //---------------------------------------------------------------------------------------------
#define TMPL template <int size>
#define TCL AbstractBoard<size>

    TMPL
    inline void TCL::remove(cell_t cell) {
        cell_ref_t ref = ref_for(cell);
        bitmask_t val = ~gameBoard[cell];

        setCount--;
        gameBoard[cell] = 0;
        boardMask[cell] = 0;
        rowConflicts[ref.row] &= val;
        colConflicts[ref.col] &= val;
        boxConflicts[ref.box] &= val;
    }

    TMPL
    inline void TCL::set(cell_t cell, bitmask_t val) {
        cell_ref_t ref = ref_for(cell);

        setCount++;
        gameBoard[cell] = val;
        boardMask[cell] = MASK;
        rowConflicts[ref.row] |= val;
        colConflicts[ref.col] |= val;
        boxConflicts[ref.box] |= val;
    }

    TMPL
    inline void TCL::mask(cell_t cell, bitmask_t mask) {
        boardMask[cell] |= mask;
    }

    TMPL
    inline void TCL::clear_mask(cell_t cell) {
        boardMask[cell] = 0;
    }

    TMPL
    inline void TCL::update_candidates(cell_t cell) {
        cell_ref_t ref = ref_for(cell);

        candidates[cell] = ((~(boardMask[cell] |
                               rowConflicts[ref.row] |
                               colConflicts[ref.col] |
                               boxConflicts[ref.box])) & MASK);
    }

    TMPL
    inline bitmask_t TCL::get_val(int row, int col) const {
        return gameBoard[row * UNIT + col];
    }

    TMPL
    inline bitmask_t TCL::get_val(cell_t cell) const {
        return gameBoard[cell];
    }

    TMPL
    inline bitmask_t TCL::get_candidates(cell_t cell) const {
        return candidates[cell];
    }

    TMPL
    inline bool TCL::is_full() const {
        return setCount == GRID;
    }

    TMPL
    inline bool TCL::is_solved() const {
        return is_full() && is_valid();
    }

    TMPL
    inline int TCL::get_filled_count() const {
        return setCount;
    }

    TMPL
    inline bool TCL::is_cell_empty(cell_t cell) const {
        return gameBoard[cell] == 0;
    }

#undef TMPL
#undef TCL
}

#endif //CSUDOKU_BOARDABSTRACT_H
