#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>  
#include <stdexcept>
#include "CSR.h"       
#include "DenseMatrix.h"  

void compare_performance(unsigned int m, unsigned int n, double sparsity, std::ofstream& out_file) {
    
    std::map<std::pair<unsigned int, unsigned int>, double> dok;
    unsigned int non_zero_count = static_cast<unsigned int>((m * n) * sparsity);

    for (unsigned int i = 0; i < non_zero_count; ++i) {
        unsigned int row = rand() % m;
        unsigned int col = rand() % n;
        dok[{row, col}] = rand() % 10 + 1; 
    }

    Matrix dense_matrix(m, n);
    for (const auto& entry : dok) {
        dense_matrix[entry.first.first][entry.first.second] = entry.second; 
    }

    
    CSRMatrix csr(dok, m, n);  

  
    std::vector<double> vec(n, 1.0);

 
    auto start_dense = std::chrono::high_resolution_clock::now();
    std::vector<double> dense_result = dense_matrix * vec;
    auto end_dense = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dense_duration = end_dense - start_dense;

    auto start_csr = std::chrono::high_resolution_clock::now();  
    std::vector<double> csr_result = csr * vec;
    auto end_csr = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> csr_duration = end_csr - start_csr;

    out_file << m << "x" << n << "," << sparsity << ","
             << dense_duration.count() << "," << csr_duration.count() << "\n";
    std::cout << "Matrix size: " << m << "x" << n << ", Sparsity: " << sparsity << std::endl;
    std::cout << "Dense matrix multiplication time: " << dense_duration.count() << " seconds" << std::endl;
    std::cout << "CSR matrix multiplication time: " << csr_duration.count() << " seconds" << std::endl;
}

int main() {

    std::ofstream out_file("performance_results.csv");

    out_file << "Matrix Size, Sparsity, Dense Time (s), CSR Time (s)\n";


    unsigned int sizes[] = {100, 1000, 10000};
    double sparsities[] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};


    for (double sparsity : sparsities) {
        for (unsigned int size : sizes) {
            compare_performance(size, size, sparsity, out_file);
        }
    }

   
    out_file.close();

    return 0;
}
