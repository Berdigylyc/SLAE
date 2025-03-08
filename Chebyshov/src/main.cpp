#include <iostream>
#include <cmath>
#include <vector>
#include "Chebyshev.h"

int main() {
    Matrix A = {{4, 1}, {1, 3}};
    Vector b = {1, 2};
    
    double lambda_max = find_lambda_max(A);
    double lambda_min = 2.382;  
    
    Vector x_cheb = Chebyshev_MSI(A, b, 2048, lambda_min, lambda_max);
    
    std::cout << "Chebyshev solution: ";
    for (double xi : x_cheb) std::cout << xi << " ";
    
    return 0;
}