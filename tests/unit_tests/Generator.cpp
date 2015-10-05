#include "catch.hpp"
#include <CSudokuLib/sudoku.h>
#include <CSudokuLib/BoardReader.h>
#include <CSudokuLib/ScrambleSolve.h>
#include <CSudokuLib/BoardReducer.h>

TEST_CASE("Board reducer should give legal boards", "[BoardReducer]") {
    using namespace sudoku;
    util::initialize();

    SECTION("Generate unique non-solved boards") {
        Board board;
        ScrambleSolve<3> solver;
        BoardReducer<3> reducer(24);
        QuickSolve<3> quickSolve(2);

        for (int i = 0; i < 50; i++) {
            board.reset();
            solver.solve(board);
            reducer.reduce_board(board);

            // Ensure its removing some cells
            REQUIRE(board.get_filled_count() < 60);

            // Ensure unique solution
            REQUIRE(quickSolve.solve(board) == 1);
        }
    }

    SECTION("Generate boards with low (<17) clues will fail") {
        Board board;
        ScrambleSolve<3> solver;
        BoardReducer<3> reducer(1);
        QuickSolve<3> quickSolve(2);

        for (int i = 15; i < 24; i++) {
            board.reset();
            solver.solve(board);
            reducer.set_target(i);
            bool success = reducer.reduce_board(board);

            // Either target is >= 17 or we have to fail
            REQUIRE((!success || (i >= 17)));
        }
    }
}
