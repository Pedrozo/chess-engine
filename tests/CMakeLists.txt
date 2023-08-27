include(CTest)

add_executable(TestPosition TestPosition.cpp)

target_include_directories(TestPosition PUBLIC doctest)
target_link_libraries(TestPosition PUBLIC chess-engine)
set_target_properties(TestPosition PROPERTIES CXX_STANDARD 17)

add_test(TestPosition TestPosition)
