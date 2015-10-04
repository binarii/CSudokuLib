#ifndef CSUDOKU_QUICKSOLVE_H
#define CSUDOKU_QUICKSOLVE_H

#include "SolveMethod.h"
#include "Indexing.h"

namespace sudoku {
    template <int size>
    class QuickSolve : public Indexing<size> {
    public:
        QuickSolve();
        ~QuickSolve();

        int solve(AbstractBoard<size> &board);
        void set_max_soln_count(int count);

    private:
        int backtrack_solve(AbstractBoard<size> &board);
        int find_single(AbstractBoard<size> &board, cell_t& pos, bitmask_t& value);

    protected: // Make sure we can see imported symbols
        using Indexing<size>::BOX;
        using Indexing<size>::UNIT;
        using Indexing<size>::GRID;
        using Indexing<size>::MASK;
        using Indexing<size>::ref_for;
        using Indexing<size>::iterate;

    private:
        int maxSolnCount;
    };
}

#endif //CSUDOKU_QUICKSOLVE_H
