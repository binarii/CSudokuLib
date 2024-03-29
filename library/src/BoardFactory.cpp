#include "BoardFactory.h"
#include "BoardReducer.h"
#include "Minimizers.h"

#define TMPL template <int size>
#define TCL BoardFactory<size>

namespace sudoku {

    TMPL TCL::BoardFactory(int minClues, SYMMETRY_TYPE type, int trials) {
        ourChooser = NULL;
        set_min_clues(minClues);
        set_max_tries(trials);
        set_symmetry(type);
    }


    TMPL TCL::~BoardFactory() {
        if (ourChooser) {
            delete ourChooser;
            ourChooser = 0;
        }
    }

    TMPL void TCL::create(AbstractBoard<size> &board) {
        int trialNum = 0;
        int lowest = board.GRID;
        AbstractBoard<size> tester;

        BoardReducer<size> reducer(chooser, minClues);
        while (trialNum++ < trialCount) {
            tester.reset();
            solver.solve(tester);
            reducer.reduce_board(tester);

            if (tester.get_filled_count() < lowest) {
                lowest = tester.get_filled_count();
                board.copy(tester);
            }

            if (board.get_filled_count() <= minClues) {
                break;
            }
        }
    }

    TMPL AbstractBoard<size> TCL::create() {
        AbstractBoard<size> board;
        create(board);
        return board;
    }

    TMPL void TCL::set_symmetry(SYMMETRY_TYPE type) {
        switch (type) {
            case ST_NONE:
                ourChooser = new SymmetryNone<size>();
                chooser = ourChooser;
                break;
            case ST_DIAGONAL:
                ourChooser = new SymmetryDiagonal<size>();
                chooser = ourChooser;
                break;
            case ST_HORIZONTAL:
                ourChooser = new SymmetryHorizontal<size>();
                chooser = ourChooser;
                break;
            case ST_CORNER:
                ourChooser = new SymmetryCorners<size>();
                chooser = ourChooser;
                break;
            case ST_TOTAL:
                break;
        }
    }

    TMPL void TCL::set_chooser(CellChooser<size> *c) {
        if (ourChooser) {
            delete ourChooser;
            ourChooser = 0;
        }

        chooser = c;
    }

    TMPL void TCL::set_max_tries(int max) {
        trialCount = max;
    }

    TMPL void TCL::set_min_clues(int min) {
        minClues = min;
    }


    template
    class BoardFactory<3>;


}

#undef TMPL
#undef TCL