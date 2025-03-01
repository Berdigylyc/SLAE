#include "solvers.h"
#include <cmath>


std::pair<std::vector<double>, int> Simple_iterationCSR(const CSRMatrix& A, const std::vector<double>& b, double tau, double epsilon, int maxIterations) {
    int n = A.getRows();
    std::vector<double> x(n, 0.0);  
    std::vector<double> x_new(n);
    int iterations = 0;

    for (int k = 0; k < maxIterations; ++k) {
        std::vector<double> Ax = A * x;

        for (int i = 0; i < n; ++i) {
            x_new[i] = x[i] - tau * (Ax[i] - b[i]);
        }

        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::abs(x_new[i] - x[i]);
        }

        iterations++;

        if (error < epsilon) {
            break;
        }

        x = x_new;
    }

    return {x, iterations};
}


std::pair<std::vector<double>, int> jacobiCSR(const CSRMatrix& A, const std::vector<double>& b, double epsilon, int maxIterations) {
    int n = A.getRows();
    std::vector<double> x(n, 0.0);  
    std::vector<double> x_new(n);
    int iterations = 0;

    for (int k = 0; k < maxIterations; ++k) {
        std::vector<double> Ax = A * x;

        for (int i = 0; i < n; ++i) {
            double sum = Ax[i] - A.getValue(i, i) * x[i];  
            x_new[i] = (b[i] - sum) / A.getValue(i, i);  
        }

        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::abs(x_new[i] - x[i]);
        }

        iterations++;

        if (error < epsilon) {
            break;
        }

        x = x_new;
    }

    return {x, iterations};
}


std::pair<std::vector<double>, int> gaussSeidelCSR(const CSRMatrix& A, const std::vector<double>& b, double epsilon, int maxIterations) {
    int n = A.getRows();
    std::vector<double> x(n, 0.0);  
    int iterations = 0;

    for (int k = 0; k < maxIterations; ++k) {
        double error = 0.0;

        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            unsigned int row_start = A.getRowPtr()[i];
            unsigned int row_end = A.getRowPtr()[i + 1];

            for (unsigned int j = row_start; j < row_end; ++j) {
                unsigned int col = A.getColIndices()[j];
                if (col != i) {  
                    sum += A.getValues()[j] * x[col];
                }
            }

            double x_new = (b[i] - sum) / A.getValue(i, i); 
            error += std::abs(x_new - x[i]);
            x[i] = x_new;
        }

        iterations++;

        if (error < epsilon) {
            break;
        }
    }

    return {x, iterations};
}