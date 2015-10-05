SET(LIB_SRC
        src/AbstractBoard.cpp
        src/BoardReader.cpp
        src/util.cpp
        src/QuickSolve.cpp
        src/ScrambleSolve.cpp src/BoardReducer.cpp)

SET(LIB_HEADER
        include/CSudokuLib/AbstractBoard.h
        include/CSudokuLib/sudoku_types.h
        include/CSudokuLib/Dimensions.h
        include/CSudokuLib/Indexing.h
        include/CSudokuLib/util.h
        include/CSudokuLib/prerequisites.h
        include/CSudokuLib/SolveMethod.h
        include/CSudokuLib/QuickSolve.h
        include/CSudokuLib/sudoku.h
        include/CSudokuLib/Stopwatch.h
        include/CSudokuLib/BoardReader.h
        include/CSudokuLib/ScrambleSolve.h include/CSudokuLib/CellChooser.h include/CSudokuLib/BoardReducer.h)


add_library(SudokuLib STATIC ${LIB_SRC} ${LIB_HEADER})

# Public include path, requires the library be prefixed with folder name
target_include_directories(SudokuLib PUBLIC
        "${CMAKE_SOURCE_DIR}/library/include")

# Private include path for use within this module
target_include_directories(SudokuLib PRIVATE
        "${CMAKE_SOURCE_DIR}/library/include/CSudokuLib")
