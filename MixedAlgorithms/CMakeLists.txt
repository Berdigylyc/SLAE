cmake_minimum_required(VERSION 3.10)
project(SLAUSolvers)
include_directories(include)


add_library(CSR src/CSR.cpp)


add_library(solvers src/solvers.cpp)


add_executable(main src/main.cpp)
target_link_libraries(main CSR solvers)

add_executable(test1 tests/test.cpp)
target_link_libraries(test1 CSR solvers)


enable_testing()

add_test(NAME Test1 COMMAND test1)
