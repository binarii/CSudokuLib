#ifndef CSUDOKU_INDEXING_H
#define CSUDOKU_INDEXING_H

#include "sudoku_types.h"
#include "Dimensions.h"

namespace sudoku {

    template<int size>
    class Indexing : public Dimensions<size> {
    public:
        Indexing();
        cell_ref_t ref_for(int index) const;
        cell_t iterate(int unit, int offset) const;

    protected: // make sure we can see the imported symbols
        using Dimensions<size>::BOX;
        using Dimensions<size>::UNIT;
        using Dimensions<size>::GRID;
        using Dimensions<size>::MASK;

        static const int GROUP_COUNT = UNIT * 3;
        static const int GROUP_SIZE = UNIT;

    private:
        void try_init();

        static bool initialized;
        static cell_t groups[GROUP_COUNT * GROUP_SIZE];
        static cell_ref_t cellReferences[Dimensions<size>::GRID];
    };


    //---------------------------------------------------------------------------------------------
    // Begin Static Initializer
    //---------------------------------------------------------------------------------------------
    template<int size>
    bool Indexing<size>::initialized = false;

    template<int size>
    cell_t Indexing<size>::groups[Indexing<size>::GROUP_COUNT * Indexing<size>::GROUP_SIZE];

    template<int size>
    cell_ref_t Indexing<size>::cellReferences[Dimensions<size>::GRID];


    //---------------------------------------------------------------------------------------------
    // Begin Class Definitions
    //---------------------------------------------------------------------------------------------
    template<int size>
    Indexing<size>::Indexing() {
        try_init();
    }

    template<int size>
    void Indexing<size>::try_init() {
        if (initialized) {
            return;
        } else {
            initialized = true;
            for (cell_t i = 0; i < GRID; i++) {
                cell_ref_t ref;
                ref.col = i % UNIT;
                ref.row = i / UNIT;
                ref.box = ((ref.col / BOX) * BOX) + (ref.row / BOX);
                cellReferences[i] = ref;

                int boxIndex = (ref.col % BOX) + (ref.row % BOX) * BOX;
                groups[(ref.row + UNIT * 0) * GROUP_SIZE + ref.col] = i;
                groups[(ref.col + UNIT * 1) * GROUP_SIZE + ref.row] = i;
                groups[(ref.box + UNIT * 2) * GROUP_SIZE + boxIndex] = i;
            }
        }
    }

    template<int size>
    inline cell_t Indexing<size>::iterate(int unit, int offset) const {
        return groups[unit * GROUP_SIZE + offset];
    }

    template<int size>
    inline cell_ref_t Indexing<size>::ref_for(int index) const {
        return cellReferences[index];
    }
}

#endif //CSUDOKU_INDEXING_H
