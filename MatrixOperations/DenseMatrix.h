#pragma once
#include <vector>

class Matrix {
private:
    unsigned int m{0}, n{0};
    std::vector<std::vector<double>> matrix;

public:
    Matrix(unsigned int m, unsigned int n);

    void push_back(unsigned int row, unsigned int col, double v);
     std::vector<double> operator*(const std::vector<double>& vec) const;
    std::vector<double>& operator[](unsigned int row);
};