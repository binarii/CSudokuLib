#include <map>
#include <iostream>
#include <CSudokuLib/sudoku.h>

#include "ArgParser.h"
#include "StringUtils.h"
#include "FormatOptions.h"


void print_board(sudoku::Board &board, sudoku::Board &unsolved, CommandArgs &args) {
    if (args.pretty) {
        sudoku::util::print_board(board, std::cout);
    } else if (args.format != "") {
        sudoku::Board copy(unsolved);
        sudoku::QuickSolve<3> solver(2);
        sudoku::BoardGrader grader;
        FormatOptions map;

        auto report = grader.grade(copy);
        copy.copy(unsolved);

        bool unique = solver.solve(copy) == 1;
        solver.set_max_soln_count(1);
        solver.solve(copy);

        map.add("unsolvedBoard", sudoku::util::encode_board(unsolved));
        map.add("unsolvedPretty", sudoku::util::pretty_board(unsolved));
        map.add("solvedBoard", sudoku::util::encode_board(copy));
        map.add("solvedPretty", sudoku::util::pretty_board(copy));
        map.add("board", sudoku::util::encode_board(board));
        map.add("pretty", sudoku::util::pretty_board(board));

        map.add("grade", report.totalScore());
        map.add("gradeInfo", report.toString());
        map.add("count", board.get_filled_count());
        map.add("solved", board.is_solved());
        map.add("valid", board.is_valid());
        map.add("unique", unique);

        std::cout << replace_all_dict(args.format, map) << std::endl;
    } else {
        std::cout << sudoku::util::encode_board(board) << std::endl;
    }
}


void generate_puzzles(CommandArgs &args) {
    sudoku::Board board;
    sudoku::BoardFactory<3> factory(15, static_cast<sudoku::SYMMETRY_TYPE>(args.symmetry), 1);

    for (int i = 0; i < args.number; i++) {
        factory.create(board);
        print_board(board, board, args);
    }
}

void load_puzzles(CommandArgs &args) {
    std::string line;
    sudoku::Board board;
    while (std::getline(std::cin, line) != 0) {
        sudoku::util::decode_board(board, line);
        print_board(board, board, args);
    }
}

void solve_puzzles(CommandArgs &args) {
    std::string line;
    sudoku::Board board;
    sudoku::Board unsolved;
    sudoku::QuickSolve<3> solver;
    while (std::getline(std::cin, line) != 0) {
        sudoku::util::decode_board(board, line);
        unsolved.copy(board);
        solver.solve(board);
        print_board(board, unsolved, args);
    }
}

void grade_puzzles(CommandArgs &args) {
    std::string line;
    sudoku::Board board;
    sudoku::Board unsolved;
    sudoku::BoardGrader grader;
    while (std::getline(std::cin, line) != 0) {
        sudoku::util::decode_board(board, line);
        unsolved.copy(board);
        auto report = grader.grade(board);

        if (args.format == "") {
            std::cout << report.totalScore() << "\t";
        }
        print_board(board, unsolved, args);
    }
}

int main(int argc, char **args) {
    Stopwatch stopwatch;
    sudoku::util::initialize();

    auto params = parseArguments(argc, args);
    if (params.rng) {
        srand(time(NULL));
    }

    if (params.command == "gen") {
        generate_puzzles(params);
    } else if (params.command == "solve") {
        solve_puzzles(params);
    } else if (params.command == "grade") {
        grade_puzzles(params);
    } else if (params.command == "") {
        load_puzzles(params);
    } else {
        std::cerr << "Error occurred: unrecognized command '" << params.command << "'" << std::endl;
    }


//    if (vm.count("command")) {
//        std::string command = vm["command"].as<std::string>();
//        if (command == "gen") {
//            generate_puzzles(arguments);
//        } else if (command == "solve") {
//            solve_puzzles(arguments);
//        } else {
//            std::cerr << "Error occurred: Cannot understand command." << std::endl;
//        }
//    } else {
//        load_puzzles(arguments);
//    }

    std::cerr << "Task completed in " << stopwatch.get_elapsed_ms() << "ms." << std::endl;

    return 0;
}
