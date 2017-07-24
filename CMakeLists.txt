cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

set(PROJECT_NAME selftest)
set(TARGET selftest)

file(GLOB MYSOLUTIONS solutions/*.cpp)
file(GLOB MYLIB lib/*.cpp)

include_directories(lib .)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES
    "*usr/include/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp"
    )
  setup_target_for_coverage(NAME ${TARGET}_coverage EXECUTABLE ${TARGET})
endif() # CMAKE_BUILD_TYPE STREQUAL "Debug"


add_executable(${TARGET} selftest.cpp ${MYSOLUTIONS} ${MYLIB})
target_compile_options(${TARGET} PRIVATE -std=c++11 -Wall -Werror -Wextra -Weffc++)

add_executable(selfbench selfbench.cpp selftest.cpp ${MYSOLUTIONS} ${MYLIB})
target_compile_options(selfbench PRIVATE -std=c++11 -Wall -Werror -Wextra -DSELFBENCH)
target_link_libraries(selfbench benchmark)

enable_testing()
add_test(test ${TARGET})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TARGET})

include(ConfigGBench)
