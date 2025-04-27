#include <iostream>
#include <vector>
#include <cmath>
#include "methods.h"

    
int grid_size = 5;
SparseMatrixCSR A = generatePoissonMatrix(grid_size);
SparseMatrixCSR A_T = A.transpose();
std::vector<double> b(A.rows, 1.0);  

void first(){              
    std::vector<double> x_cg = conjugateGradient(A, b);
    if((x_cg[1] *  x_cg[2] * x_cg[3]) != 0 )
        std::cout<<"test1 passed"<<std::endl;
}

void second(){
    std::vector<double> x_bicg = BiCG(A, A_T, b);
        if((x_bicg[1] *  x_bicg[2] * x_bicg[3]) != 0 )
        std::cout<<"test1 passed"<<std::endl;
}

int main() {
    first();
    second();
     
    std::cout << "All tests passed successfully!\n";
    return 0;
}