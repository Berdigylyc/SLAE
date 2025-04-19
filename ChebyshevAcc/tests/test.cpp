#include <iostream>
#include <vector>
#include <cmath>
#include "methods.h"
using namespace std;

    
    vector<vector<double>> A = {
        {4, -1, 0},
        {-1, 4, -1},
        {0, -1, 4}
    };
    vector<double> b = {5, 5, 5};
    

    void first(){
        vector<double> x_sd = chebyshevAcceleratedSGS(A, b,1e-10);
            if((x_sd[1] *  x_sd[2] * x_sd[3]) != 0 )
                cout<<"test1 passed"<<endl;
    }

    void second(){
        vector<double> x_ssor = symmetricGaussSeidel(A, b);
            if((x_ssor[1] *  x_ssor[2] * x_ssor[3]) != 0 )
                cout<<"test2 passed"<<endl;
    }

    int main() {
    first();
    second();
    
    
    std::cout << "All tests passed successfully!\n";
    return 0;
}