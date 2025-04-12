/*#include <iostream>
#include <vector>
#include <cmath>
#include "methods.h"

using namespace std;

    vector<vector<double>> generateSPDMatrix(int n) {
        vector<vector<double>> A(n, vector<double>(n, 0.0));
        
        
        for(int i = 0; i < n; ++i) {
            A[i][i] = 4.0;  
            if(i > 0) A[i][i-1] = -1.0;  
            if(i < n-1) A[i][i+1] = -1.0;  
        }
        return A;
    }
    
    vector<double> generateVector(int n, double value = 5.0) {
        return vector<double>(n, value);  
    }

int main() {
    

    auto A = generateSPDMatrix(1000);
    auto b = generateVector(1000);
    
    vector<double> x_sd = steepestDescent(A, b);
    vector<double> x_ssor = symmetricGaussSeidel(A, b);
    vector<double> x_sor = SOR(A, b);
    
    
    auto printVec = [](const vector<double>& v) {
        for (double val : v) cout << val << " ";
        cout << endl;
    };
    
    cout << "Steepest Descent: ";
    printVec(x_sd);
    
    cout << "Symmetric Gauss-Seidel: ";
    printVec(x_ssor);
    
    cout << "SOR: ";
    printVec(x_sor);
    
    return 0;
}
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include "methods.h"

using namespace std;

vector<vector<double>> generateSPDMatrix(int n) {
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    for(int i = 0; i < n; ++i) {
        A[i][i] = 4.0;
        if(i > 0) A[i][i-1] = -1.0;
        if(i < n-1) A[i][i+1] = -1.0;
    }
    return A;
}

vector<double> generateVector(int n, double value = 5.0) {
    return vector<double>(n, value);
}

int main() {
    const int n = 1000;
    const double tol = 1e-6;
    const int maxIter = 1000;
    
    auto A = generateSPDMatrix(n);
    auto b = generateVector(n);

    ofstream datafile("sor_times.csv");
    datafile << "omega,time\n";

    
    for (int i = 0; i < 100; ++i) {
        double omega = 0.01 + 0.02 * i;
        
        auto start = chrono::high_resolution_clock::now();
        vector<double> x = SOR(A, b, omega, tol, maxIter);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double> duration = end - start;
        datafile << omega << "," << duration.count() << "\n";
    }

    datafile.close();
    cout << "Timing data written to sor_times.csv" << endl;
    return 0;
}
