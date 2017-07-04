cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")

set(TEST_SOURCES
  main.cpp
  3sum_closest.cpp
  regular_expression_matching.cpp
)

add_executable(selftest ${TEST_SOURCES})
