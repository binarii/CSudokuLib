#include <sstream>
#include "util.h"
#include "AbstractBoard.h"

namespace sudoku {
    namespace util {
        int BitCountArray[1 << 10];

        bool initialize() {
            for (int i = 0; i < (1 << 10); i++) {
                BitCountArray[i] = bitcount((bitmask_t) i);
            }

            return true;
        }

        int mask_to_int(sudoku::bitmask_t mask) {
            return sudoku::util::bitcount(sudoku::util::get_lsb(mask) - 1);
        }

        sudoku::bitmask_t int_to_mask(int value) {
            return (sudoku::bitmask_t) (1 << value);
        }

        void print_board(const Board &board, std::ostream &stream) {
            const int UNIT = Dimensions<3>::UNIT;
            const int BOX = Dimensions<3>::BOX;

            for (int row = 0; row < UNIT; row++) {
                if (row > 0 && row % BOX == 0) {
                    stream << "------+-------+------" << std::endl;
                }

                for (int col = 0; col < UNIT; col++) {
                    if (col > 0 && col % BOX == 0) {
                        stream << "| ";
                    }

                    int val = mask_to_int(board.get_val(row, col));
                    if (val == 0) stream << ".";
                    else stream << val;
                    stream << " ";
                }
                stream << std::endl;
            }
            stream << std::endl;
        }

        std::string pretty_board(const Board &board) {
            std::stringstream stream;
            print_board(board, stream);
            std::string out = stream.str();
            out.pop_back();
            return out;
        }

        bool decode_board(Board &board, const std::string &puzzle) {
            const int GRID = Dimensions<3>::GRID;
            if (puzzle.length() != GRID) {
                return false;
            }

            board.reset();
            for (cell_t i = 0; i < GRID; i++) {
                char c = puzzle[i];
                if ((c > '0') && (c <= '9')) {
                    board.set(i, int_to_mask(c - '0'));
                } else if ((c >= 'a') && (c <= 'z')) {
                    board.set(i, int_to_mask(c - 'a' + 10));
                }
            }

            return true;
        }

        std::string encode_board(const Board &board, const char zeroVal) {
            std::string result = "";

            for (cell_t i = 0; i < Dimensions<3>::GRID; i++) {
                int valueAt = mask_to_int(board.get_val(i));
                char c = '0' + (char) valueAt;
                if (valueAt == 0) c = zeroVal;
                result += c;
            }

            return result;
        }
    }
}