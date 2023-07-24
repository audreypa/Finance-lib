#ifndef PATH_GENERATION_H
#define PATH_GENERATION_H

#include <vector>
#include <cmath>

double gaussian_box_muller2() {
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

//Provides vector with sample points of a GBM
void calc_path_spot_prices(std::vector<double>& spot_prices, const double& r,
                           const double& v, const double& T) {
    double dt = T/static_cast<double>(spot_prices.size());
    double drift = exp(dt*(r-0.5*v*v));
    double vol = sqrt(v*v*dt);

    for (std::vector<double>::size_type i = 1; i < spot_prices.size(); i++) {
        double gauss_bm = gaussian_box_muller2();
        spot_prices[i] = spot_prices[i-1] * drift * exp(vol*gauss_bm);
    }

}

#endif // PATH_GENERATION_H
