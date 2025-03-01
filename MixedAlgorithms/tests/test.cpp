#include "CSR.h"
#include "solvers.h"
#include <iostream>
#include <map>
#include <cmath>


bool areVectorsEqual(const std::vector<double>& v1, const std::vector<double>& v2, double tolerance = 1e-6) {
    if (v1.size() != v2.size()) return false;
    for (size_t i = 0; i < v1.size(); ++i) {
        if (std::abs(v1[i] - v2[i]) > tolerance) return false;
    }
    return true;
}

int main() {

    std::map<std::pair<unsigned int, unsigned int>, double> dok = {
        {{0, 0}, 4.0}, {{0, 1}, -1.0},
        {{1, 0}, -1.0}, {{1, 1}, 4.0}, {{1, 2}, -1.0},
        {{2, 1}, -1.0}, {{2, 2}, 4.0}
    };
    CSRMatrix A(dok, 3, 3);


    std::vector<double> b = {15.0, 10.0, 10.0};


    std::vector<double> expected_solution = {5.0, 4.0, 3.0};

    double epsilon = 1e-6;
    int maxIterations = 1000;


    auto result_mpi = Simple_iterationCSR(A, b, 0.1, epsilon, maxIterations);
    if (areVectorsEqual(result_mpi.first, expected_solution)) {
        std::cout << "Simple Iteration (MPI) test passed!\n";
    } else {
        std::cout << "Simple Iteration (MPI) test failed!\n";
    }


    auto result_jacobi = jacobiCSR(A, b, epsilon, maxIterations);
    if (areVectorsEqual(result_jacobi.first, expected_solution)) {
        std::cout << "Jacobi test passed!\n";
    } else {
        std::cout << "Jacobi test failed!\n";
    }


    auto result_gs = gaussSeidelCSR(A, b, epsilon, maxIterations);
    if (areVectorsEqual(result_gs.first, expected_solution)) {
        std::cout << "Gauss-Seidel test passed!\n";
    } else {
        std::cout << "Gauss-Seidel test failed!\n";
    }

    return 0;
}