cmake_minimum_required(VERSION 3.0.0)
project(chess_engine VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

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
  src/chess/knight_attack.cpp
  src/chess/king_attack.cpp
  src/chess/pawns_attack.cpp
  src/chess/board/square_centric.cpp
  src/chess/board/piece_centric.cpp
  src/chess/search/generate_moves.cpp
  src/chess/search/state_machine.cpp
)

target_include_directories(chess_engine PUBLIC ./inc)
set_target_properties(chess_engine PROPERTIES CXX_STANDARD 23)
# target_compile_options(chess_engine PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_subdirectory(tests)
