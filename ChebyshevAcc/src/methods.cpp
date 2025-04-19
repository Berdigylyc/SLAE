#include <vector>
#include <cmath>
#include "methods.h"

namespace LinearAlgebra {
    vector<double> vectorSub(const vector<double>& a, const vector<double>& b) {
        vector<double> res(a.size());
        for (size_t i = 0; i < a.size(); ++i) res[i] = a[i] - b[i];
        return res;
    }

    vector<double> matVecMult(const vector<vector<double>>& A, const vector<double>& x) {
        vector<double> res(x.size(), 0.0);
        for (size_t i = 0; i < A.size(); ++i)
            for (size_t j = 0; j < A[i].size(); ++j)
                res[i] += A[i][j] * x[j];
        return res;
    }

    double vectorNorm(const vector<double>& v) {
        double norm = 0.0;
        for (auto x : v) norm += x*x;
        return sqrt(norm);
    }
}

vector<double> symmetricGaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol,  int maxIter){
    
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_half(n);
    
    for (int iter = 0; iter < maxIter; ++iter) {
        for (int i = 0; i < n; ++i) {
            double sum = b[i];
            for (int j = 0; j < i; ++j)
                sum -= A[i][j] * x_half[j];
            for (int j = i+1; j < n; ++j)
                sum -= A[i][j] * x[j];
            x_half[i] = sum / A[i][i];
        }
        
        
        for (int i = n-1; i >= 0; --i) {
            double sum = b[i];
            for (int j = 0; j < i; ++j)
                sum -= A[i][j] * x_half[j];
            for (int j = i+1; j < n; ++j)
                sum -= A[i][j] * x[j];
            x[i] = sum / A[i][i];
        }
        
        vector<double> r = LinearAlgebra::vectorSub(b, LinearAlgebra::matVecMult(A, x));
         //double currentNorm = LinearAlgebra::vectorNorm(r);
         //cout << "Iteration: " << iter + 1 << ", Residual norm: " << currentNorm << endl;
        
        
        if (LinearAlgebra::vectorNorm(r) < tol) 
            
            break;
    
    }
    return x;
}

vector<double> chebyshevAcceleratedSGS(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter, double rho) 
{
    int n = A.size();
    vector<double> y0(n, 0.0), y1(n, 0.0), y2(n);

   
    auto SGS_step = [&](const vector<double>& x) -> vector<double> {
        vector<double> x_new = x;
        vector<double> x_half(n);
        
        
        for (int i = 0; i < n; ++i) {
            double sum = b[i];
            for (int j = 0; j < i; ++j) sum -= A[i][j] * x_half[j];
            for (int j = i+1; j < n; ++j) sum -= A[i][j] * x_new[j];
            x_half[i] = sum / A[i][i];
        }
        
        
        for (int i = n-1; i >= 0; --i) {
            double sum = b[i];
            for (int j = 0; j < i; ++j) sum -= A[i][j] * x_half[j];
            for (int j = i+1; j < n; ++j) sum -= A[i][j] * x_new[j];
            x_new[i] = sum / A[i][i];
        }
        return x_new;
    };

    y1 = SGS_step(y0);  
    double omega = 1.0 / (1.0 - rho*rho/4.0);  
    
    for (int iter = 0; iter < maxIter; ++iter) {
        
        vector<double> Py = SGS_step(y1);
        for (int i = 0; i < n; ++i) {
            y2[i] = omega * (Py[i] - y0[i]) + y0[i];
        }

        
        vector<double> r = LinearAlgebra::vectorSub(b, LinearAlgebra::matVecMult(A, y2));
        if (LinearAlgebra::vectorNorm(r) < tol) break;

        
        y0 = y1;
        y1 = y2;
        
        
        omega = 1.0 / (1.0 - rho*rho * omega / 4.0);
    }

    return y2;
}