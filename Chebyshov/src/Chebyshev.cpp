#include <iostream>
#include <cmath>
#include <vector>
#include "Chebyshev.h"

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Vector;

Vector operator*(const Matrix &A, const Vector &x) {
    int n = A.size();
    Vector res(n, 0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i] += A[i][j] * x[j];
    return res;
}

double dot(const Vector &x, const Vector &y) {
    double res = 0.0;
    for (size_t i = 0; i < x.size(); ++i)
        res += x[i] * y[i];
    return res;
}

double norm(const Vector &x) {
    return std::sqrt(dot(x, x));
}

double find_lambda_max(const Matrix &A, unsigned int max_iter, double tol) {
    unsigned int n = A.size();
    Vector r(n, 1.0);
    double lambda = 0.0;
    
    for (unsigned int i = 0; i < max_iter; ++i) {
        Vector Ar = A * r;
        double new_lambda = dot(r, Ar) / dot(r, r);
        if (std::abs(lambda - new_lambda) < tol) break;
        lambda = new_lambda;
        double norm_Ar = norm(Ar);
        for (size_t j = 0; j < n; ++j)
            r[j] = Ar[j] / norm_Ar;
    }
    return lambda;
}

std::vector<int> generate_chebyshev_sorter(int r) {
    std::vector<int> sorted = {0, 1};  
    
    for (int current_r = 2; current_r <= r; ++current_r) {
        int max_idx = (1 << current_r) - 1;
        std::vector<int> new_sorted;
        
        for (int k : sorted) {
            new_sorted.push_back(k);
            new_sorted.push_back(max_idx - k);
        }
        sorted = new_sorted;
    }
    return sorted;
}

std::vector<double> chebyshev_tau(unsigned int n, double a, double b) {
    std::vector<double> tau(n);
        
    for (unsigned int k = 0; k < n; ++k) {
        double theta = M_PI * (2*k + 1) / (2*n);
        double t_k = std::cos(theta);
        double scaled_t = (a + b)/2.0 + (b - a)/2.0 * t_k;
        tau[k] = 1.0 / scaled_t;
    }

    int r = 0;
    unsigned int temp = n;
    while (temp >>= 1) ++r;
    
    std::vector<int> perm = generate_chebyshev_sorter(r);
    std::vector<double> tau_permuted(n);
    
    for (unsigned int i = 0; i < n; ++i)
        tau_permuted[i] = tau[perm[i]];
    
    return tau_permuted;
}

Vector Chebyshev_MSI(const Matrix &A, const Vector &b, unsigned int steps, double lambda_min, double lambda_max, unsigned int &steps_taken, double tol) {
    unsigned int n = A.size();
    Vector x(n, 0.0);
    std::vector<double> tau = chebyshev_tau(steps, lambda_min, lambda_max);
    
    steps_taken = 0;
    for (unsigned int k = 0; k < steps; ++k) {
        Vector Ax = A * x;
        Vector residual(n);
        
        for (size_t i = 0; i < n; ++i)
            residual[i] = Ax[i] - b[i];
        
        for (size_t i = 0; i < n; ++i)
            x[i] -= tau[k] * residual[i];
        
        steps_taken++;
        
        if (norm(residual) < tol) break;
    }
    return x;
}

