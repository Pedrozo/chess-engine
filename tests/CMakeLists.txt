include(CTest)

add_executable(test_bitboards test_bitboards.cpp)

target_include_directories(test_bitboards PRIVATE doctest/)
target_link_libraries(test_bitboards PRIVATE chess_engine)
set_target_properties(test_bitboards PROPERTIES CXX_STANDARD 23)
target_compile_options(test_bitboards PRIVATE -Wall -Wextra -Wpedantic)

add_test(test_bitboards test_bitboards)
