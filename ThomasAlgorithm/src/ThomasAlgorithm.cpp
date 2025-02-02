#include <iostream>
#include "Algorithm.h"

void ReadVector(const std::string& name, std::vector<double>& vec, int size) {
    std::cout << "Enter " << size << " values for vector " << name << ": ";
    for (int i = 0; i < size; ++i) {
        std::cin >> vec[i];
    }
}

int main() {

    std::cout<<"Welcome to the Thomas algorithm SLAE solver"<<std::endl;
    int n;
    std::cout << "Please enter the number of equations: ";
    std::cin >> n;

    std::vector<double> a(n);
    std::vector<double> b(n);   
    std::vector<double> c(n);
    std::vector<double> d(n);   
    std::vector<double> x(n);   

    ReadVector("a (subdiagonal)", a, n-1);
    ReadVector("b (main diagonal)", b, n);
    ReadVector("c (superdiagonal)", c, n-1);
    ReadVector("d (right side vector)", d, n);

    ThomasAlgorithm(a, b, c, d, x);

    std::cout << "The calculated solution vector x: ";
    for (double val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}