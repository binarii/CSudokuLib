#include "BoardReader.h"
#include "util.h"

namespace sudoku {

    BoardReader::BoardReader(std::string filename) : file(filename) { }

    BoardReader::~BoardReader() {
        file.close();
    }

    BoardIterator BoardReader::begin() {
        return {file, false};
    }

    BoardIterator BoardReader::end() {
        return {file, true};
    }

    BoardIterator::BoardIterator(std::ifstream &f, bool isEnd) : file(f) {
        eof = isEnd || std::getline(file, line) == 0;
        if (!eof) util::decode_board(board, line);
    }

    Board &BoardIterator::operator*() {
        return board;
    }

    bool BoardIterator::operator!=(const BoardIterator &it) const {
        return eof != it.eof;
    }

    BoardIterator &BoardIterator::operator++() {
        eof = std::getline(file, line) == 0;
        if (!eof) util::decode_board(board, line);
        return *this;
    }
}