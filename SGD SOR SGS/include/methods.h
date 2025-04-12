#pragma once
#include <vector>
using namespace std;

vector<double> steepestDescent(const vector<vector<double>>& A, const vector<double>& b, double tol = 1e-6, int maxIter = 1000);
vector<double> symmetricGaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol = 1e-6, int maxIter = 1000);
vector<double> SOR(const vector<vector<double>>& A, const vector<double>& b, double omega = 1.5, double tol = 1e-6, int maxIter = 1000);

