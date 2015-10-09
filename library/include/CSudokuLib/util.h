#ifndef CSUDOKU_UTIL_H
#define CSUDOKU_UTIL_H

#include <string>
#include <random>
#include <iostream>
#include "prerequisites.h"

namespace sudoku {
    namespace util {

        //---------------------------------------------------------------------
        // Call this before using the library
        //---------------------------------------------------------------------
        bool initialize();


        //---------------------------------------------------------------------
        // Board IO
        //---------------------------------------------------------------------
        std::string pretty_board(const Board &board);
        void print_board(const Board &board, std::ostream &stream);
        bool decode_board(Board &board, const std::string &puzzle);
        std::string encode_board(const Board &board, const char zeroVal = '.');

        int mask_to_int(sudoku::bitmask_t mask);
        sudoku::bitmask_t int_to_mask(int value);


        //---------------------------------------------------------------------
        // Bitmask operations
        //---------------------------------------------------------------------
        inline bitmask_t get_lsb(bitmask_t mask) {
            return (mask & -mask);
        }

        inline int bitcount(bitmask_t val) {
            val -= (val >> 1) & 0x55555555;
            val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
            val = (val + (val >> 4)) & 0x0f0f0f0f;
            val += val >> 8;
            val += val >> 16;
            return val & 0x1f;
        }

        inline int bitcount_cached(bitmask_t val) {
            extern int BitCountArray[1 << 10];
            return BitCountArray[val];
        }


        // Fischer-Yates shuffle
        template<typename T>
        void shuffle_array(T *arr, int n) {
            int second, tail;
            for (int i = 0; i < n; i++) {
                tail = n - i;
                second = rand() % tail + i;

                T tmp = arr[i];
                arr[i] = arr[second];
                arr[second] = tmp;
            }
        }
    }
}

#endif //CSUDOKU_UTIL_H
