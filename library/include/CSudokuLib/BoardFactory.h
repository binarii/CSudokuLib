#ifndef CSUDOKU_BOARDFACTORY_H
#define CSUDOKU_BOARDFACTORY_H

#include "prerequisites.h"
#include "ScrambleSolve.h"
#include "CellChooser.h"

namespace sudoku {

    typedef enum {
        ST_NONE,
        ST_DIAGONAL,
        ST_HORIZONTAL,
        ST_CORNER,
        ST_TOTAL
    } SYMMETRY_TYPE;


    template<int size>
    class BoardFactory {
    public:
        BoardFactory(int minClues = 30, SYMMETRY_TYPE type = ST_NONE, int trials = 100);
        ~BoardFactory();

        void create(AbstractBoard<size> &board);
        AbstractBoard<size> create();

        void set_min_clues(int min);
        void set_max_tries(int max);
        void set_symmetry(SYMMETRY_TYPE type);
        void set_chooser(CellChooser<size> *c);
    private:
        int minClues;
        int trialCount;
        ScrambleSolve<size> solver;
        CellChooser<size> *chooser;
        CellChooser<size> *ourChooser;
    };
}

#endif //CSUDOKU_BOARDFACTORY_H
