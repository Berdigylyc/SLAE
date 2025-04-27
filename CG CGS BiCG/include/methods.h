#pragma once
#include <iostream>
#include <vector>

struct SparseMatrixCSR 
{
    std::vector<double> values;   
    std::vector<int> columns;     
    std::vector<int> row_ptr;    
    int rows;                    
    int cols;                  

    SparseMatrixCSR(int n_rows, int n_cols) : rows(n_rows), cols(n_cols) 
    {
        row_ptr.resize(n_rows + 1, 0);
    }


    std::vector<double> operator*(const std::vector<double>& x) const {
        if (x.size() != cols) {
            throw std::invalid_argument("Несовместимые размеры матрицы и вектора.");
        }

        std::vector<double> result(rows, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int j = row_ptr[i]; j < row_ptr[i+1]; ++j) {
                result[i] += values[j] * x[columns[j]];
            }
        }
        return result;
    }

    SparseMatrixCSR transpose() const {
        SparseMatrixCSR transposed(cols, rows);
        transposed.row_ptr.resize(cols + 1, 0);

        for (int col : columns) {
            transposed.row_ptr[col + 1]++;
        }

        for (int i = 1; i <= cols; ++i) {
            transposed.row_ptr[i] += transposed.row_ptr[i - 1];
        }

        transposed.values.resize(values.size());
        transposed.columns.resize(values.size());
        std::vector<int> count(cols, 0);

        for (int i = 0; i < rows; ++i) {
            for (int j = row_ptr[i]; j < row_ptr[i + 1]; ++j) {
                int col = columns[j];
                int dest = transposed.row_ptr[col] + count[col]++;
                transposed.values[dest] = values[j];
                transposed.columns[dest] = i;
            }
        }
        return transposed;
    }
};

SparseMatrixCSR generatePoissonMatrix(int grid_size);
std::vector<double> conjugateGradient(const SparseMatrixCSR& A, const std::vector<double>& b, double tol = 1e-6, int max_iter = 1000);
std::vector<double> BiCG(const SparseMatrixCSR& A,const SparseMatrixCSR& A_T, const std::vector<double>& b, double tol = 1e-6, int max_iter = 1000);
