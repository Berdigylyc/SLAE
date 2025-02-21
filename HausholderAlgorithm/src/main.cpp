#include <iostream>
#include "DenseMatrix.h"

int main() {
    Matrix A(3, 3);
    A.push_back(0, 0, 12); A.push_back(0, 1, -51); A.push_back(0, 2, 4);
    A.push_back(1, 0, 6); A.push_back(1, 1, 167); A.push_back(1, 2, -68);
    A.push_back(2, 0, -4); A.push_back(2, 1, 24); A.push_back(2, 2, -41);

    Matrix Q(3, 3);
    Matrix R(3, 3);

    householderQR(A, Q, R);

    std::cout << "Q:" << std::endl;
    Q.print();

    std::cout << "R:" << std::endl;
    R.print();

    return 0;
}