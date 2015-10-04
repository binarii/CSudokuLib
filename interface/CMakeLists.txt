SET(CLI_SRC
        src/Main.cpp)

add_executable(SudokuCLI
        ${CLI_SRC})

target_link_libraries(SudokuCLI SudokuLib)
