include(CTest)

file(GLOB_RECURSE test_files *.cpp)

foreach(test_file IN LISTS test_files)
  message(${test_file})
  get_filename_component(test_exec ${test_file} NAME_WE)

  add_executable(${test_exec} ${test_file})

  target_include_directories(${test_exec} PRIVATE doctest/)
  target_link_libraries(${test_exec} PRIVATE chess_engine)
  set_target_properties(${test_exec} PROPERTIES CXX_STANDARD 23)
  target_compile_options(${test_exec} PRIVATE -Wall -Wextra -Wpedantic)

  add_test(${test_exec} ${test_exec})

endforeach()
