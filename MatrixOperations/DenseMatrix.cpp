#include "DenseMatrix.h"
#include <stdexcept>
Matrix::Matrix(unsigned int m, unsigned int n)
    : m{m}, n{n} {
    matrix.resize(m, std::vector<double>(n, 0.0));
}

void Matrix::push_back(unsigned int row, unsigned int col, double v) {
    matrix[row][col] = v;
}

std::vector<double>& Matrix::operator[](unsigned int row) {
    return matrix[row];
}

std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
    if (vec.size() != n) {
        throw std::invalid_argument("Matrix columns must match the vector size.");
    }

    std::vector<double> result(m, 0.0); 

  
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }

    return result; 
}