#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <stdexcept> 
#include "methods.h"


int main() {
    try {
        std::ofstream datafile("CG_times.csv");
        datafile << "Size,time\n";
        for (int i = 10; i < 100; ++i) {
            int grid_size = i;
            SparseMatrixCSR A = generatePoissonMatrix(grid_size);
            SparseMatrixCSR A_T = A.transpose(); 
            std::vector<double> b(A.rows, 1.0); 
            
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<double> x_cg = conjugateGradient(A, b);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Время выполнения CG: " << duration.count() << " мс\n";
            datafile << i << "," << duration.count() << "\n";
        }
        
        datafile.close();
        std::cout << "Timing data written to CG_times.csv" << std::endl;

        std::ofstream datafile2("Bicg_times.csv");
        datafile2 << "Size,time\n";
        for (int i = 10; i < 100; ++i) {
            int grid_size = i;
            SparseMatrixCSR A = generatePoissonMatrix(grid_size);
            SparseMatrixCSR A_T = A.transpose(); 
            std::vector<double> b(A.rows, 1.0); 
            
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<double> x_bicg = BiCG(A, A_T, b);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Время выполнения BiCG: " << duration.count() << " мс\n";
            datafile2 << i << "," << duration.count() << "\n";  
        }
        datafile2.close();
        std::cout << "Timing data written to BiCG_times.csv" << std::endl;        

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

