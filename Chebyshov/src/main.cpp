#include <iostream>
#include <cmath>
#include <vector>
#include "Chebyshev.h"


int main() {
   
     
    const int size = 10000;
    Matrix A_large(size, Vector(size, 0.0));
    Vector b_large(size, 0.0);


    for (int i = 0; i < size; ++i) {
        A_large[i][i] = 4.0;
        if (i > 0) A_large[i][i-1] = 1.0;
        if (i < size - 1) A_large[i][i+1] = 1.0;
        b_large[i] = i + 1;
    }


    double lambda_max_large = find_lambda_max(A_large);
    double lambda_min_large = 2.0; 

    
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int large_steps_taken;
    Vector x_large = Chebyshev_MSI(A_large, b_large, 2048, lambda_min_large, lambda_max_large, large_steps_taken);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\n10000x10000 Matrix Results:" << std::endl;
    std::cout << "Steps taken: " << large_steps_taken << std::endl;
    std::cout << "Time taken: " << duration << " ms" << std::endl;

    return 0;
}