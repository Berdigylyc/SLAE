#include "CSR.h"
#include "solvers.h"
#include <iostream>
#include <map>
#include <chrono>
#include <cstdlib>  
#include <ctime>    


CSRMatrix generateRandomMatrix(int size) {
    std::map<std::pair<unsigned int, unsigned int>, double> dok;
    srand(time(0));  

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
               
                dok[{i, j}] = static_cast<double>(rand() % 100) + 100.0;  
            } else if (std::abs(i - j) <= 5) {  
                dok[{i, j}] = static_cast<double>(rand() % 100) - 50.0; 
            }
        }
    }

    return CSRMatrix(dok, size, size);
}

int main() {
    int size{0};
    std::cout<<"Please enter the size of Matrix"<<std::endl;
    std::cin>>size;  
    std::cout<<"Please wait!"<<std::endl;
    CSRMatrix A = generateRandomMatrix(size);

    
    std::vector<double> b(size);
    for (int i = 0; i < size; ++i) {
        b[i] = static_cast<double>(rand() % 100) - 50.0;  
    }

    double epsilon = 1e-6;
    int maxIterations = 1000000;  

    
    auto start = std::chrono::high_resolution_clock::now();
    auto result_mpi = Simple_iterationCSR(A, b, 0.1, epsilon, maxIterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "MSI: Iterations = " << result_mpi.second << ", Elapsed time = " << elapsed.count() << " seconds\n";

   
    start = std::chrono::high_resolution_clock::now();
    auto result_jacobi = jacobiCSR(A, b, epsilon, maxIterations);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Jacobi: Iterations = " << result_jacobi.second << ", Elapsed time = " << elapsed.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    auto result_gs = gaussSeidelCSR(A, b, epsilon, maxIterations);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Gauss-Seidel: Iterations = " << result_gs.second << ", Elapsed time = " << elapsed.count() << " seconds\n";

    return 0;
}