cmake_minimum_required(VERSION 3.10)

project(Chebyshev LANGUAGES CXX)

include_directories(include)

add_library(Chebyshev src/Chebyshev.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main Chebyshev)


add_executable(test_Chebyshev tests/test.cpp)
target_link_libraries(test_Chebyshev Chebyshev)


enable_testing()
add_test(NAME Chebyshev_Test COMMAND test_Chebyshev)

