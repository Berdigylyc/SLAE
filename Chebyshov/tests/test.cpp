#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include "Chebyshev.h"

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Vector;

void test_permutations() {
    auto test_r = [](int r, const std::vector<int>& expected) {
        auto result = generate_chebyshev_sorter(r);
        assert(result == expected);
    };

    test_r(1, {0, 1});
    test_r(2, {0, 3, 1, 2});
    test_r(3, {0, 7, 3, 4, 1, 6, 2, 5});
    std::cout << "Permutation tests passed!\n";
}

void test_eigenvalues() {
    Matrix A = {{4, 1}, {1, 3}};
    double computed_max = find_lambda_max(A);
    double expected_max = (7 + std::sqrt(5))/2;  // ~5.618
    assert(std::abs(computed_max - expected_max) < 1e-4);
    std::cout << "Eigenvalue test passed!\n";
}

void test_chebyshev_nodes() {
    auto test_nodes = [](unsigned n, double a, double b) {
        auto tau = chebyshev_tau(n, a, b);
        assert(tau.size() == n);
        
        for(double t : tau) {
            double lambda = 1.0/t;
            assert(lambda >= a && lambda <= b);
        }
    };

    test_nodes(4, 2.0, 5.0);
    test_nodes(8, 1.0, 10.0);
    std::cout << "Chebyshev nodes tests passed!\n";
}

void test_solver() {
    Matrix A = {{4, 1}, {1, 3}};
    Vector b = {1, 2};
    Vector exact = {1.0/11, 7.0/11};  
    
    Vector solution = Chebyshev_MSI(A, b, 16, 2.381966, 5.618034, 1e-6);
    
    assert(std::abs(solution[0] - exact[0]) < 1e-6);
    assert(std::abs(solution[1] - exact[1]) < 1e-6);
    std::cout << "Solver test passed!\n";
}

int main() {
    test_permutations();
    test_eigenvalues();
    test_chebyshev_nodes();
    test_solver();
    
    std::cout << "All tests passed successfully!\n";
    return 0;
}