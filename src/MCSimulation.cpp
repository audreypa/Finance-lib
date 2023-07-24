#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

//random number with Box Muller alorithm
//We can use std::normal_distribution in <random> instead

std::default_random_engine generator;
std::normal_distribution<double> distribution(0.0,1.0);


double gaussian_box_muller() {
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;

    //generating two uniform random variables until the square of their "euclidean distance"
    //is less than unity

    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        euclid_sq = x*x + y*y;
    } while (euclid_sq >= 1.0);

    return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

//Pricing European vanilla call with MC
double monte_carlo_call_price(const int& num_sims, const double& S,
                              const double& K, const double& r,
                              const double& v, const double& T) {

    double S_adjust = S * exp(T*(r-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for (int i=0; i<num_sims; i++) {
        //double gauss_bm = gaussian_box_muller();
        double random_N = distribution(generator);
        S_cur = S_adjust * exp(sqrt(v*v*T)*random_N);
        payoff_sum += std::max(S_cur - K, 0.0);
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

double monte_carlo_put_price(const int& num_sims, const double& S,
                              const double& K, const double& r,
                              const double& v, const double& T) {

    double S_adjust = S * exp(T*(r-0.5*v*v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for (int i=0; i<num_sims; i++) {
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
        payoff_sum += std::max(K - S_cur, 0.0);
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

/*int main(int argc, char **argv) {
    int num_sims = 1000000;
    double S = 100.0;
    double K = 100.0;
    double r = 0.05;
    double v = 0.2;
    double T = 1.0;

    double call = monte_carlo_call_price(num_sims,S, K, r, v, T);
    double put = monte_carlo_put_price(num_sims,S, K, r, v, T);

    std::cout << "Paths:         " << num_sims << std::endl;
    std::cout << "Underlying:    " << S << std::endl;
    std::cout << "Strike:        " << K << std::endl;
    std::cout << "Rf:            " << r << std::endl;
    std::cout << "Volatility:    " << v << std::endl;
    std::cout << "Maturity:      " << T << std::endl;

    std::cout << "Call Price:    " << call << std::endl;
    std::cout << "Put Price:     " << put << std::endl;

    return 0;
}*/
