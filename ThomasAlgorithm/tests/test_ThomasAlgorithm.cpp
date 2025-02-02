#include "Algorithm.h"
#include <cassert>
#include <iostream>
#include<vector>

void testThomasAlgorithm() {
    std::vector<double> y = {0, 0, 0};
    std::vector<double> a = {1, 1}; 
    std::vector<double> b = {2, 2, 2};  
    std::vector<double> c = {1, 1}; 
    std::vector<double> d = {1, 2, 3}; 

    std::vector<double> expected = {0.5, 0, 1.5};
    ThomasAlgorithm(a, b, c, d, y);

    assert(y == expected);
    std::cout << "Test passed!" << std::endl;
}

int main() {
    testThomasAlgorithm();
    return 0;
}
