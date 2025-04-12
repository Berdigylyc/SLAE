#include <vector>
#include <cmath>
#include"methods.h"


using namespace std;

class LinearAlgebra {
    public:
        
        static vector<double> matVecMult(const vector<vector<double>>& A, const vector<double>& x) {
            int n = A.size();
            vector<double> res(n, 0.0);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    res[i] += A[i][j] * x[j];
            return res;
        }
    
        static double dotProduct(const vector<double>& a, const vector<double>& b) {
            double res = 0.0;
            for (size_t i = 0; i < a.size(); ++i)
                res += a[i] * b[i];
            return res;
        }
    
        static double vectorNorm(const vector<double>& v) {
            return sqrt(dotProduct(v, v));
        }
    
        static vector<double> vectorSub(const vector<double>& a, const vector<double>& b) {
            vector<double> res(a.size());
            for (size_t i = 0; i < a.size(); ++i)
                res[i] = a[i] - b[i];
            return res;
        }
};
 
vector<double> steepestDescent(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter){
    int n = A.size();
    vector<double> x (n, 0.0);
    vector<double> r = LinearAlgebra::vectorSub(b, LinearAlgebra::matVecMult(A, x));  
    
    for(int i = 0; i < maxIter; ++i){
        vector<double> Ar = LinearAlgebra::matVecMult(A, r);
        double alpha = LinearAlgebra::dotProduct(r, r) / LinearAlgebra::dotProduct(r, Ar); 

        for(int i=0; i < n; ++i)
            x[i] += alpha * r[i]; 
                    
        r = LinearAlgebra::vectorSub(b, LinearAlgebra::matVecMult(A, x));
        if(LinearAlgebra::vectorNorm(r) < tol) 
            break;
    }

    return x;
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
        if (LinearAlgebra::vectorNorm(r) < tol)
            break;
    }
    return x;
}


vector<double> SOR(const vector<vector<double>>& A, const vector<double>& b,double omega, double tol, int maxIter){
    
        int n = A.size();
        vector<double> x(n, 0.0);
        
        for (int iter = 0; iter < maxIter; ++iter) {
            for (int i = 0; i < n; ++i) {
                double sum = b[i];
                for (int j = 0; j < i; ++j)
                    sum -= A[i][j] * x[j];
                for (int j = i+1; j < n; ++j)
                    sum -= A[i][j] * x[j];
                x[i] = (1 - omega) * x[i] + omega * (sum / A[i][i]);
            }
            
            vector<double> r = LinearAlgebra::vectorSub(b, LinearAlgebra::matVecMult(A, x));
            if (LinearAlgebra::vectorNorm(r) < tol)
                break;
        }
        return x;
    
}
