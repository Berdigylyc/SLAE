#include <iostream>
#include "DenseMatrix.h"

int main() {
    Matrix A(2, 2);
    A.push_back(0, 0, 1);
    A.push_back(0, 1, 2);
    A.push_back(1, 0, 3);
    A.push_back(1, 1, 4);

    if (A[0][0] == 1 && A[1][1] == 4) {
        std::cout << "Test passed!" << std::endl;
        return 0;
    } else {
        std::cout << "Test failed!" << std::endl;
        return 1;
    }
}