SET(TEST_SRC
        Main.cpp
        Util.cpp
        Solvers.cpp)

add_executable(SudokuTest
        ${TEST_SRC})

target_link_libraries(SudokuTest SudokuLib)

target_include_directories(SudokuTest PUBLIC
        "${CMAKE_SOURCE_DIR}/tests/include")
