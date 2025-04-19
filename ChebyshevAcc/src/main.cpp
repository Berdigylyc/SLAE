#include <vector>
#include <cmath>
#include <functional>
#include <iostream>
#include <chrono>
#include <fstream>
#include "methods.h"

using namespace std;



vector<vector<double>> generateSPDMatrix(int n) {
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        A[i][i] = 4.0 + i * 0.1; 
        if (i > 0) A[i][i-1] = A[i-1][i] = -1.0 + rand() % 3 * 0.1; 
        if (i < n-1) A[i][i+1] = A[i+1][i] = -1.0 + rand() % 3 * 0.1;
    }
    return A;
} 

vector<double> generateVector(int n) {
    vector<double> b(n);
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        b[i] = 100.0 + i * 0.5 + (rand() % 100) * 0.01; // Неоднородность + шум
    }
    return b;
}



int main() {
    const int       n = 1000;
    const double  tol = 1e-6;
    const int maxIter = 1000;
    
    

    ofstream datafile("sor_times.csv");
    datafile << "n, iterations, time\n";

    
    for (int i = 0; i < 1000; ++i) {
        double m = 100 + i;
        
        auto A = generateSPDMatrix(m);
        auto b = generateVector(m);
        auto start = chrono::high_resolution_clock::now();
        
        vector<double> solution = chebyshevAcceleratedSGS(A, b, 1e-10, 1000);
        
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double> duration = end - start;
        datafile << A.size() << ", " << duration.count() << "\n";
    }

    datafile.close();
    cout << "Timing data written to sor_times.csv" << endl;
    return 0;
}



