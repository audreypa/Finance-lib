#include <iostream>
#include <cmath>
#include "statistics.h"

//Initialization standard normal distribution
StandardNormalDistribution N;

//Computation of d_j for j in {1,2} so d1 and d2
double d_j(const int& j, const double& S, const double& K, const double& r,
           const double& v, const double& T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

double call_price(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return S *N.cdf(d_j(1, S, K, r, v, T)) - K*exp(-r*T) *
    N.cdf(d_j(2, S, K, r, v, T));
}

double put_price(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return -S *N.cdf(-d_j(1, S, K, r, v, T)) + K*exp(-r*T) *
    N.cdf(-d_j(2, S, K, r, v, T));
}

/*int main(int argc, char **argv) {
    double S = 100.0;
    double K = 100.0;
    double r = 0.05;
    double v = 0.2;
    double T = 1.0;

    double call = call_price(S, K, r, v, T);
    double put = put_price(S, K, r, v, T);

    std::cout << "Underlying:    " << S << std::endl;
    std::cout << "Strike:        " << K << std::endl;
    std::cout << "Rf:            " << r << std::endl;
    std::cout << "Volatility:    " << v << std::endl;
    std::cout << "Maturity:      " << T << std::endl;

    std::cout << "Call Price:    " << call << std::endl;
    std::cout << "Put Price:     " << put << std::endl;

    return 0;
}*/
