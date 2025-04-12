cmake_minimum_required(VERSION 3.10)

project(hw LANGUAGES CXX)

include_directories(include)

add_library(methods src/methods.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE methods)


add_executable(test_hw tests/test.cpp)
target_link_libraries(test_hw methods)


enable_testing()
add_test(NAME hw_Test COMMAND test_hw)

