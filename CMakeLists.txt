cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

set(PROJECT_NAME selftest)
set(TARGET selftest)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Weffc++ ${CMAKE_CXX_FLAGS}")

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
  )

add_executable(${TARGET} ${TEST_SOURCES})

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
