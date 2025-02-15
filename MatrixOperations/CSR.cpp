#include "CSR.h"
#include <iostream>
CSRMatrix::CSRMatrix(const std::map<std::pair<unsigned int, unsigned int>, double>& dok, unsigned int rows, unsigned int cols)
    : m(rows), n(cols) {
    row_ptr.push_back(0);

    for (unsigned int i = 0; i < m; ++i) {
        unsigned int count = 0;
        for (unsigned int j = 0; j < n; ++j) {
            auto key = std::make_pair(i, j);
            if (dok.count(key)) {
                values.push_back(dok.at(key));
                col_indices.push_back(j);
                count++;
            }
        }
        row_ptr.push_back(row_ptr.back() + count);
    }
}

std::vector<double> CSRMatrix::operator*(const std::vector<double>& vec) const {
    if (vec.size() != n) {
        throw std::invalid_argument("Vector size does not match matrix columns");
    }

    std::vector<double> result(m, 0.0);

    for (unsigned int i = 0; i < m; ++i) {
        unsigned int start = row_ptr[i];
        unsigned int end = row_ptr[i + 1];
        for (unsigned int j = start; j < end; ++j) {
            result[i] += values[j] * vec[col_indices[j]];
        }
    }

    return result;
}

void CSRMatrix::print() const {
    std::cout << "Values: ";
    for (double val : values) std::cout << val << " ";
    std::cout << "\nColumn Indices: ";
    for (unsigned int col : col_indices) std::cout << col << " ";
    std::cout << "\nRow Pointers: ";
    for (unsigned int row : row_ptr) std::cout << row << " ";
    std::cout << std::endl;
}