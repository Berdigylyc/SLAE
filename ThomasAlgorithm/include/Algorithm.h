#include<vector>

void ThomasAlgorithm(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c, const std::vector<double>& d,  std::vector<double>& x){
    // Here a is subdiaganal, b is maindiagonal, c is superdiagonal vectors, d is right side vector, x is unknown
    
    int n = b.size();
    std::vector<double> p(n),q(n);

    p[1] = -c[0]/b[0];
    q[1] = d[0]/b[0];

    for (int i = 1; i<n-1; ++i){
        double D = a[i] * p[i] + b[i];
        p[i+1] = -c[i] / D;
        q[i+1] = (d[i] - a[i] * q[i]) / D;
    }

    x[n-1] = (d[n-1]-a[n-1]*q[n-1])/(a[n-1]*p[n-1]+b[n-1]);

    for (int i = n-1; i > 0; --i){
        x[i-1] = p[i]*x[i] + q[i];
    }
}