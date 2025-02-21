#pragma once
#include <vector>
#include <map>
#include <stdexcept>

class CSRMatrix {
private:
    std::vector<double> values;
    std::vector<unsigned int> col_indices;
    std::vector<unsigned int> row_ptr;
    unsigned int m;
    unsigned int n;

public:
    CSRMatrix(const std::map<std::pair<unsigned int, unsigned int>, double>& dok, unsigned int rows, unsigned int cols);

    std::vector<double> operator*(const std::vector<double>& vec) const;

    void print() const;
};