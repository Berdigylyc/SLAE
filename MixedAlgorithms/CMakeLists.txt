cmake_minimum_required(VERSION 3.10)

project(Mixed_Operations LANGUAGES CXX)

include_directories(include)

add_library(solvers src/solvers.cpp)
add_library(CSR src/CSR.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main solvers CSR)


#add_executable(test tests/test.cpp)
#target_link_libraries(test solvers CSR)


#enable_testing()
#add_test(NAME Test COMMAND Test)

