#ifndef CSUDOKU_BOARDREADER_H
#define CSUDOKU_BOARDREADER_H

#include <fstream>
#include <iostream>
#include "util.h"
#include "prerequisites.h"
#include "AbstractBoard.h"

namespace sudoku {

    class BoardIterator {
    public:
        BoardIterator(std::ifstream &f, bool isEnd);

        bool operator!=(const BoardIterator &it) const;
        BoardIterator &operator++();
        Board &operator*();

    private:
        std::ifstream &file;
        std::string line;
        Board board;
        bool eof;
    };

    class BoardReader {
    public:
        BoardReader(std::string filename);
        ~BoardReader();

        BoardIterator begin();
        BoardIterator end();

    private:
        std::ifstream file;
    };
}

#endif //CSUDOKU_BOARDREADER_H
