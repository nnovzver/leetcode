cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Weffc++ ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")

set(TEST_SOURCES
  main.cpp
  3sum_closest.cpp
  4sum.cpp
  regular_expression_matching.cpp
  longest_common_prefix.cpp
  letter_combinations_phone_number.cpp
)

add_executable(selftest ${TEST_SOURCES})
