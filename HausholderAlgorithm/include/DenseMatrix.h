#pragma once
#include <vector>
#include <cmath>

class Matrix {
private:
    unsigned int m{0}, n{0};
    std::vector<std::vector<double>> matrix;

public:
    Matrix(unsigned int m, unsigned int n);

    void push_back(unsigned int row, unsigned int col, double v);
    std::vector<double> operator*(const std::vector<double>& vec) const;
    Matrix operator*(double scalar) const;
    std::vector<double>& operator[](unsigned int row);
    const std::vector<double>& operator[](unsigned int row) const;

    unsigned int rows() const { return m; }
    unsigned int cols() const { return n; }

    void print() const;
};

void householderQR(const Matrix& A, Matrix& Q, Matrix& R);
