#include "catch.hpp"
#include <CSudokuLib/sudoku.h>
#include <CSudokuLib/BoardReader.h>
#include <CSudokuLib/ScrambleSolve.h>

TEST_CASE("Solve Methods should be able to solve puzzles", "[QuickSolve][ScrambleSolve]") {
    sudoku::util::initialize();

    SECTION("Quicksolve") {
        auto fn = "puzzles/top1465.txt";
        sudoku::BoardReader br(fn);
        sudoku::QuickSolve<3> solver;
        int solvedCount = 0, totalCount = 0;

        for (auto &board : br) {
            solver.solve(board);

            totalCount += 1;
            solvedCount += board.is_solved() ? 1 : 0;
        }

        REQUIRE(solvedCount == totalCount);
    }

    SECTION("ScrambleSolve") {
        sudoku::Board board;
        sudoku::ScrambleSolve<3> solver;
        int solvedCount = 0, max = 50;
        for (int i = 0; i < max; i++) {
            board.reset();
            solver.solve(board);

            if (board.is_solved()) {
                solvedCount++;
            }
        }

        REQUIRE(solvedCount == max);
    }
}
