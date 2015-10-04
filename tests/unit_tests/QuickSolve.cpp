#include "catch.hpp"
#include <CSudokuLib/sudoku.h>
#include <CSudokuLib/BoardReader.h>


TEST_CASE("Quicksolve should be able to solve puzzles", "[QuickSolve]") {
    sudoku::util::initialize();

    sudoku::QuickSolve<3> solver;
    int solvedCount = 0, totalCount = 0;

    auto fn = "puzzles/top1465.txt";
    sudoku::BoardReader br(fn);
    for (auto& board : br) {
        solver.solve(board);

        totalCount += 1;
        solvedCount += board.is_solved() ? 1 : 0;
    }

    REQUIRE(solvedCount == totalCount);
}
