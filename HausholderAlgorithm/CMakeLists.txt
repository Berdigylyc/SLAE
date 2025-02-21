cmake_minimum_required(VERSION 3.10)

project(Hausholders_Algorithm LANGUAGES CXX)

include_directories(include)

add_library(DenseMatrix src/DenseMatrix.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main DenseMatrix)


add_executable(test_Hausholders_Algorithm tests/test.cpp)
target_link_libraries(test_Hausholders_Algorithm DenseMatrix)


enable_testing()
add_test(NAME Hausholders_Algorithm_Test COMMAND test_Hausholders_Algorithm)

