#include "catch.hpp"
#include <CSudokuLib/sudoku.h>
#include <algorithm>
#include <string>

static std::string smallTestPuzzles[] = {
        "4...3.......6..8..........1....5..9..8....6...7.2........1.27..5.3....4.9........",
        "7.8...3.....2.1...5.........4.....263...8.......1...9..9.6....4....7.5...........",
        "7.8...3.....6.1...5.........4.....263...8.......1...9..9.2....4....7.5...........",
        "3.7.4...........918........4.....7.....16.......25..........38..9....5...2.6.....",
        "5..7..6....38...........2..62.4............917............35.8.4.....1......9....",
        "4..7..6....38...........2..62.5............917............43.8.5.....1......9....",
        ".4..1.2.......9.7..1..........43.6..8......5....2.....7.5..8......6..3..9........",
        "7.5.....2...4.1...3.........1.6..4..2...5...........9....37.....8....6...9.....8.",
        "......41.9..3.....3...5.....48..7..........62.1.......6..2....5.7....8......9....",
        "7.5.....2...4.1...3.........1.6..4..2...5...........9....37.....9....8...8.....6.",
        ".8..1......5....3.......4.....6.5.7.89....2.....3.....2.....1.9..67........4.....",
        "8.9...3.....7.1...5.........7.....263...9.......1...4..6.2....4....8.5...........",
        "6.9.....8...7.1...4............6...4.2.....3..3....5...1.5...7.8...9..........2..",
        "......41.9..3.....3...2.....48..7..........52.1.......5..2....6.7....8......9...."
};

TEST_CASE("Board getters and setters work", "[Board][util]") {
    sudoku::Board board;

    SECTION("Encode and decode are symmetric") {
        for (auto original : smallTestPuzzles) {
            sudoku::util::decode_board(board, original);
            std::string encoded = sudoku::util::encode_board(board);
            REQUIRE(encoded == original);
        }
    }

    SECTION("Loaded board starts in correct state") {
        for (auto original : smallTestPuzzles) {
            std::string copy = original;
            sudoku::util::decode_board(board, original);

            // Erase all periods and leave only digits
            copy.erase(std::remove(copy.begin(), copy.end(), '.'), copy.end());
            REQUIRE (copy.size() == board.get_filled_count());

            REQUIRE(board.is_valid());
            REQUIRE_FALSE(board.is_full());
            REQUIRE_FALSE(board.is_solved());
        }
    }
}
