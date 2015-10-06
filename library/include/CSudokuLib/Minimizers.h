#ifndef CSUDOKU_MINIMIZERS_H
#define CSUDOKU_MINIMIZERS_H

#include <vector>
#include <utility>
#include "Indexing.h"
#include "prerequisites.h"
#include "CellChooser.h"
#include "util.h"

#define USING_COMMON_TEMPLATES() \
    using Indexing<size>::GRID; \
    using Indexing<size>::UNIT; \
    using Indexing<size>::to_cell; \
    using detail::SymmetryBase<size>::mirror_x; \
    using detail::SymmetryBase<size>::mirror_y; \
    using detail::SymmetryBase<size>::to_cell; \
    using detail::SymmetryBase<size>::shuffle_vector; \
    typedef std::vector<std::vector<cell_t>> CellOrderVector;

namespace sudoku {

    namespace detail {

        template<int size>
        class SymmetryBase : public CellChooser<size>, public Indexing<size> {
        public:
            std::pair<int, int> mirror_x(int row, int col) {
                int nr = row, nc = Dimensions<size>::UNIT - col - 1;
                return {nr, nc};
            }

            std::pair<int, int> mirror_y(int row, int col) {
                int nr = Dimensions<size>::UNIT - row - 1, nc = col;
                return {nr, nc};
            }

            cell_t to_cell(std::pair<int, int> &pair) {
                return Indexing<size>::to_cell(pair.first, pair.second);
            }

            template<typename T>
            void shuffle_vector(std::vector<T> &vec) {
                if (vec.size() > 0)
                    util::shuffle_array(&vec[0], vec.size());
            }
        };
    }


    template<int size>
    class SymmetryNone : public detail::SymmetryBase<size> {
    public:
        USING_COMMON_TEMPLATES();

        CellOrderVector pickCells() {
            CellOrderVector order;
            for (cell_t i = 0; i < GRID; i++) {
                order.push_back({i});
            }

            shuffle_vector(order);
            return order;
        }
    };


    template<int size>
    class SymmetryDiagonal : public detail::SymmetryBase<size> {
    public:
        USING_COMMON_TEMPLATES();

        CellOrderVector pickCells() {
            CellOrderVector order;
            for (cell_t r = 0; r < UNIT; r++) {
                for (cell_t c = r; c < UNIT; c++) {
                    order.push_back({to_cell(r, c), to_cell(c, r)});
                }
            }

            shuffle_vector(order);
            return order;
        }
    };


    template<int size>
    class SymmetryHorizontal : public detail::SymmetryBase<size> {
    public:
        USING_COMMON_TEMPLATES();

        CellOrderVector pickCells() {
            CellOrderVector order;
            int middle = UNIT / 2 + UNIT % 2;
            for (cell_t r = 0; r < UNIT; r++) {
                for (cell_t c = 0; c < middle; c++) {
                    auto next = mirror_x(r, c);
                    order.push_back({to_cell(r, c), to_cell(next)});
                }
            }

            shuffle_vector(order);
            return order;
        }
    };

    template<int size>
    class SymmetryCorners : public detail::SymmetryBase<size> {
    public:
        USING_COMMON_TEMPLATES();

        CellOrderVector pickCells() {
            CellOrderVector order;
            int middle = UNIT / 2 + UNIT % 2;
            for (cell_t r = 0; r < middle; r++) {
                for (cell_t c = 0; c < middle; c++) {
                    std::vector<cell_t> curr;

                    auto na = mirror_x(r, c);
                    auto nb = mirror_y(r, c);
                    auto nc = mirror_y(na.first, na.second);

                    curr.push_back(to_cell(r, c));
                    curr.push_back(to_cell(na));
                    curr.push_back(to_cell(nb));
                    curr.push_back(to_cell(nc));
                    order.push_back(curr);
                }
            }

            shuffle_vector(order);
            return order;
        }
    };
}

#undef USING_COMMON_TEMPLATES
#endif //CSUDOKU_MINIMIZERS_H
