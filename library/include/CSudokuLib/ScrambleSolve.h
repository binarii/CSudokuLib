#ifndef CSUDOKU_SCRAMBLESOLVE_H
#define CSUDOKU_SCRAMBLESOLVE_H

#include "prerequisites.h"
#include "SolveMethod.h"
#include "Indexing.h"

namespace sudoku {
    template<int size>
    class ScrambleSolve : public SolveMethod<size>, Indexing<size> {
    public:
        ScrambleSolve();
        ~ScrambleSolve();

        int solve(AbstractBoard<size> &board);

    private:
        int backtrackSolve(AbstractBoard<size> &board);
    };
}


#endif //CSUDOKU_SCRAMBLESOLVE_H
