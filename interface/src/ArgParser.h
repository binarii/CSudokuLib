#ifndef CSUDOKU_ARGPARSER_H
#define CSUDOKU_ARGPARSER_H

#include <string>
#include <CSudokuLib/sudoku.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct CommandArgs {
    std::string format;
    std::string command;
    int number, symmetry;
    bool info, pretty, formatted, rng;

    CommandArgs(po::variables_map &vm) :
            command(vm["command"].as<std::string>()), rng(vm.count("norng") == 0),
            info(vm.count("info") != 0), pretty(vm.count("pretty") != 0),
            formatted(vm.count("format") != 0), number(vm["number"].as<int>()),
            symmetry(vm["symmetry"].as<int>()), format(vm["format"].as<std::string>()) {
    }
};

CommandArgs parseArguments(int argc, char **args) {
    po::options_description desc;
    desc.add_options()
            ("pretty,p", "Pretty print the output")
            ("info,i", "Print summary information")
            ("norng,r", "Dont seed random")
            ("command", po::value<std::string>()->default_value(""), "gen | solve")
            ("number,n", po::value<int>()->default_value(1), "Number of puzzles to process")
            ("symmetry,s", po::value<int>()->default_value(sudoku::ST_NONE), "Type of symmetry")
            ("format,f", po::value<std::string>()->default_value(""), "Specify custom output format");

    po::positional_options_description p;
    p.add("command", -1);

    po::variables_map vm;
    auto parser = po::basic_command_line_parser<char>(argc, args);
    po::store(parser.options(desc).positional(p).run(), vm);

    CommandArgs arguments(vm);
    return arguments;
}

#endif //CSUDOKU_ARGPARSER_H
