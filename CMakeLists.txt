cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

set(PROJECT_NAME selftest)
set(TARGET selftest)

set(TEST_SOURCES
  main.cpp
  3sum_closest.cpp
  4sum.cpp
  regular_expression_matching.cpp
  longest_common_prefix.cpp
  letter_combinations_phone_number.cpp
  remove_node_from_list_end.cpp
  list_node.cpp
  insertion_sort_list.cpp
  roman_to_int.cpp
  int_to_roman.cpp
  valid_parentheses.cpp
  merge_two_sorted_lists.cpp
  generate_parentheses.cpp
  merge_k_lists.cpp
  )

add_executable(${TARGET} ${TEST_SOURCES})
target_compile_options(${TARGET} PRIVATE -std=c++11 -Wall -Werror -Wextra -Weffc++)

add_executable(selfbench selfbench.cpp ${TEST_SOURCES})
target_compile_options(selfbench PRIVATE -std=c++11 -Wall -Werror -Wextra -DSELFBENCH)
target_link_libraries(selfbench benchmark)

enable_testing()
add_test(test ${TARGET})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TARGET})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CodeCoverage)
  set(COVERAGE_EXCLUDES
    "*usr/include/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp"
    )
  setup_target_for_coverage(NAME ${TARGET}_coverage EXECUTABLE ${TARGET})
endif() # CMAKE_BUILD_TYPE STREQUAL "Debug"

include(ConfigGBench)
