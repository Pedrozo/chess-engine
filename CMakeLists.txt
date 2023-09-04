cmake_minimum_required(VERSION 3.0.0)
project(chess-engine VERSION 0.1.0 LANGUAGES C CXX)

add_library(chess-engine
            src/chess/Attack.cpp
            src/chess/BitBoardSquare.cpp
            src/chess/board/PieceCentric.cpp
            src/chess/board/SquareCentric.cpp
            src/chess/hash/ZobristHashing.cpp)

target_include_directories(chess-engine PUBLIC ./inc)
set_target_properties(chess-engine PROPERTIES CXX_STANDARD 17)
target_compile_options(chess-engine PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_subdirectory(tests)
