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

<<<<<<< HEAD
void householderQR(const Matrix& A, Matrix& Q, Matrix& R);
=======
void householderQR(const Matrix& A, Matrix& Q, Matrix& R);
>>>>>>> 8a3ad846ebc43cae3d8c03bc14c59a17265225b0
