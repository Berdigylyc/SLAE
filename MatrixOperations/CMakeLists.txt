cmake_minimum_required(VERSION 3.10)


project(MatrixPerformanceComparison)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_BUILD_TYPE Release)


add_executable(main main.cpp CSR.cpp DenseMatrix.cpp)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})



