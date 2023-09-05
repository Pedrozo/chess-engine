include(CTest)

add_executable(TestRegularMoves TestRegularMoves.cpp)

target_include_directories(TestRegularMoves PUBLIC doctest)
target_link_libraries(TestRegularMoves PUBLIC chess-engine)
set_target_properties(TestRegularMoves PROPERTIES CXX_STANDARD 17)

add_test(TestRegularMoves TestRegularMoves)
