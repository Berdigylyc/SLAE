#pragma once
#include "CSR.h"
#include <vector>

std::pair<std::vector<double>, int> Simple_iterationCSR(const CSRMatrix& A, const std::vector<double>& b, double tau, double epsilon, int maxIterations);

std::pair<std::vector<double>, int> jacobiCSR(const CSRMatrix& A, const std::vector<double>& b, double epsilon, int maxIterations);

std::pair<std::vector<double>, int> gaussSeidelCSR(const CSRMatrix& A, const std::vector<double>& b, double epsilon, int maxIterations);

