#ifndef CSUDOKU_NAKED_H
#define CSUDOKU_NAKED_H

#include "Technique.h"

namespace sudoku {
    class NakedSingle : public Technique {
    public:
        int step(Board &board);
    };

    class NakedPair : public Technique {
    public:
        int step(Board &board);
    };

    class NakedTriple : public Technique {
    public:
        int step(Board &board);
    };

    class NakedQuad : public Technique {
    public:
        int step(Board &board);
    };
}


#endif //CSUDOKU_NAKED_H
