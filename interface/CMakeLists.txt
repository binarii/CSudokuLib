SET(CLI_SRC
        src/Main.cpp src/ArgParser.h src/StringUtils.h src/FormatOptions.h)

add_executable(SudokuCLI
        ${CLI_SRC})

find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(SudokuCLI SudokuLib ${Boost_LIBRARIES})
