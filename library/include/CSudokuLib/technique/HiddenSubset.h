#ifndef CSUDOKU_HIDDENSUBSET_H
#define CSUDOKU_HIDDENSUBSET_H

#include "Technique.h"

namespace sudoku {
    class HiddenSingle : public Technique {
    public:
        int step(Board &board);
    };

    class HiddenPair : public Technique {
    public:
        int step(Board &board);
    };

    class HiddenTriple : public Technique {
    public:
        int step(Board &board);
    };

    class HiddenQuad : public Technique {
    public:
        int step(Board &board);
    };
}

#endif //CSUDOKU_HIDDENSUBSET_H
