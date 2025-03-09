#pragma once
#include <vector>
#include <chrono>

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Vector;

Vector operator*(const Matrix &A, const Vector &x);
double dot(const Vector &x, const Vector &y);
double norm(const Vector &x);
double find_lambda_max(const Matrix &A, unsigned int max_iter = 1000, double tol = 1e-6);
std::vector<int> generate_chebyshev_sorter(int r);
std::vector<double> chebyshev_tau(unsigned int n, double a, double b);
Vector Chebyshev_MSI(const Matrix &A, const Vector &b, unsigned int steps, double lambda_min, double lambda_max, unsigned int &steps_taken, double tol = 1e-6);