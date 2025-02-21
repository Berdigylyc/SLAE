#include "DenseMatrix.h"
#include <stdexcept>
#include <iostream>

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

const std::vector<double>& Matrix::operator[](unsigned int row) const {
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

Matrix Matrix::operator*(double scalar) const {
    Matrix result(m, n);
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

void Matrix::print() const {
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void householderQR(const Matrix& A, Matrix& Q, Matrix& R) {
    unsigned int m = A.rows();
    unsigned int n = A.cols();

    Q = Matrix(m, m);
    R = A;

    
    for (unsigned int i = 0; i < m; ++i) {
        Q[i][i] = 1.0;
    }

    for (unsigned int k = 0; k < n; ++k) {
        double norm_x = 0.0;
        for (unsigned int i = k; i < m; ++i) {
            norm_x += R[i][k] * R[i][k];
        }
        norm_x = std::sqrt(norm_x);

        double alpha = -std::copysign(norm_x, R[k][k]);
        double beta = std::sqrt(0.5 * (1.0 - R[k][k] / alpha));

        std::vector<double> v(m, 0.0);
        v[k] = (R[k][k] - alpha) / (2.0 * alpha * beta);
        for (unsigned int i = k + 1; i < m; ++i) {
            v[i] = R[i][k] / (2.0 * alpha * beta);
        }

        
        for (unsigned int j = k; j < n; ++j) {
            double dot = 0.0;
            for (unsigned int i = k; i < m; ++i) {
                dot += v[i] * R[i][j];
            }
            for (unsigned int i = k; i < m; ++i) {
                R[i][j] -= 2.0 * v[i] * dot;
            }
        }

       
        for (unsigned int j = 0; j < m; ++j) {
            double dot = 0.0;
            for (unsigned int i = k; i < m; ++i) {
                dot += v[i] * Q[i][j];
            }
            for (unsigned int i = k; i < m; ++i) {
                Q[i][j] -= 2.0 * v[i] * dot;
            }
        }
    }
}