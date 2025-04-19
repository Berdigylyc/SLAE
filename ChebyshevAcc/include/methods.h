#pragma once
#include <vector>
using namespace std;


vector<double> symmetricGaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol = 1e-10, int maxIter = 1000);
vector<double> chebyshevAcceleratedSGS(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter = 1000, double rho = 0.8);

