cmake_minimum_required(VERSION 3.3)
project(CSudoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tests)
add_subdirectory(library)
add_subdirectory(interface)

