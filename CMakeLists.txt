cmake_minimum_required (VERSION 3.8.2)

project (Graph CXX)

find_program (CLANG-CHECK clang-check)
message(${CLANG-CHECK})

find_program(MAKE make)
message(${MAKE})

find_program(VALGRIND valgrind)
message(${VALGRIND})

set (CMAKE_CXX_STANDARD          14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS        OFF)

enable_testing()

add_executable     (TestGraph TestGraph.c++)
add_custom_command (OUTPUT TestGraph.tmp COMMAND ${VALGRIND} TestGraph > TestGraph.tmp)
add_custom_target  (TestGraph.c++x DEPENDS TestGraph.tmp)

add_test               (TestGraph.check1 ${CLANG-CHECK} -extra-arg=-std=c++11          ../TestGraph.c++ --)
add_test               (TestGraph.check2 ${CLANG-CHECK} -extra-arg=-std=c++11 -analyze ../TestGraph.c++ --)
add_test               (TestGraph        ${MAKE}                                          TestGraph.c++x)
set_property           (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES              "TestGraph.plist")
target_compile_options (TestGraph PRIVATE -pedantic -Wall -Weffc++)
target_link_libraries  (TestGraph PRIVATE gtest gtest_main)
