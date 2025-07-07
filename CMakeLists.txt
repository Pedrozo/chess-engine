cmake_minimum_required(VERSION 3.0.0)
project(chess_engine VERSION 0.1.0 LANGUAGES C CXX)

add_library(chess_engine 
  src/chess/square.cpp
  src/chess/bitboard.cpp
  src/chess/diagonal.cpp
  src/chess/antidiagonal.cpp 
  src/chess/rotated_bitboard.cpp
  src/chess/rank_attack.cpp
  src/chess/file_attack.cpp
  src/chess/diagonal_attack.cpp
  src/chess/antidiagonal_attack.cpp
)

target_include_directories(chess_engine PUBLIC ./inc)
set_target_properties(chess_engine PROPERTIES CXX_STANDARD 23)
target_compile_options(chess_engine PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_subdirectory(tests)
