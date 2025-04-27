#include <iostream>
#include <vector>
#include <cmath>
#include "methods.h"


namespace VectorOps {

    double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Векторы должны быть одного размера.");
        }
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            sum += a[i] * b[i];
        }
        return sum;
    }

    std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Векторы должны быть одного размера.");
        }
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    std::vector<double> subtract(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Векторы должны быть одного размера.");
        }
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    std::vector<double> scale(const std::vector<double>& a, double scalar) {
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] * scalar;
        }
        return result;
    }
}


std::vector<double> conjugateGradient(const SparseMatrixCSR& A, const std::vector<double>& b, double tol, int max_iter) 
{
    int n = A.rows;
    std::vector<double> x(n, 0.0); 
    std::vector<double> r = b;     
    std::vector<double> d = r;     
    double rs_old = VectorOps::dotProduct(r, r);

    for (int i = 0; i < max_iter; ++i) {
        std::vector<double> Ad = A * d;
        double alpha = rs_old / VectorOps::dotProduct(d, Ad);
        x = VectorOps::add(x, VectorOps::scale(d, alpha)); 
        r = VectorOps::subtract(r, VectorOps::scale(Ad, alpha)); 
        double rs_new = VectorOps::dotProduct(r, r);

        if (std::sqrt(rs_new) < tol) {
            std::cout << "CG сошёлся за " << i << " итераций.\n";
            break;
        }

        double beta = rs_new / rs_old;
        d = VectorOps::add(r, VectorOps::scale(d, beta)); 
        rs_old = rs_new;
    }
    return x;
}


std::vector<double> BiCG(const SparseMatrixCSR& A, const SparseMatrixCSR& A_T, const std::vector<double>& b, double tol, int max_iter) 
{
    int n = A.rows;
    std::vector<double> x(n, 0.0); 
    std::vector<double> r = VectorOps::subtract(b, A * x); 
    std::vector<double> r_tilde = r; 
    std::vector<double> d = r;      
    std::vector<double> d_tilde = r_tilde; 
    double rho_old = VectorOps::dotProduct(r_tilde, r);

    for (int i = 0; i < max_iter; ++i) {
        std::vector<double> Ad = A * d;
        std::vector<double> A_Td_tilde = A_T * d_tilde;
        double alpha = rho_old / VectorOps::dotProduct(d_tilde, Ad);
        x = VectorOps::add(x, VectorOps::scale(d, alpha)); 
        r = VectorOps::subtract(r, VectorOps::scale(Ad, alpha)); 
        r_tilde = VectorOps::subtract(r_tilde, VectorOps::scale(A_Td_tilde, alpha)); 
        double rho_new = VectorOps::dotProduct(r_tilde, r);


        if (std::sqrt(rho_new) < tol) {
            std::cout << "BiCG сошёлся за " << i << " итераций.\n";
            break;
        }

        double beta = rho_new / rho_old;
        d = VectorOps::add(r, VectorOps::scale(d, beta)); 
        d_tilde = VectorOps::add(r_tilde, VectorOps::scale(d_tilde, beta));
        rho_old = rho_new;
    }
    return x;
}


SparseMatrixCSR generatePoissonMatrix(int grid_size) 
{
    int n = grid_size * grid_size;
    SparseMatrixCSR A(n, n);
    A.row_ptr.push_back(0); 

    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            int row = i * grid_size + j;
            std::vector<int> neighbors;

            if (i > 0) neighbors.push_back((i-1)*grid_size + j);
            if (j > 0) neighbors.push_back(i*grid_size + (j-1));
            if (i < grid_size-1) neighbors.push_back((i+1)*grid_size + j);
            if (j < grid_size-1) neighbors.push_back(i*grid_size + (j+1));

            A.values.push_back(4.0);
            A.columns.push_back(row);

            for (int neighbor : neighbors) {
                A.values.push_back(-1.0);
                A.columns.push_back(neighbor);
            }

            A.row_ptr.push_back(A.values.size()); 
        }
    }
    return A;
}
