include(CTest)

add_executable(test_mate_puzzles test_mate_puzzles.cpp)

target_include_directories(test_mate_puzzles PRIVATE doctest/)
target_link_libraries(test_mate_puzzles PRIVATE chess_engine)
set_target_properties(test_mate_puzzles PROPERTIES CXX_STANDARD 23)
target_compile_options(test_mate_puzzles PRIVATE -Wall -Wextra -Wpedantic)

add_test(test_mate_puzzles test_mate_puzzles)
