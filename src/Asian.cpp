#ifndef ASIAN_CPP
#define ASIAN_CPP

#include <numeric>
#include <cmath>
#include "Asian.h"

//====================
//AsianOption
//====================

AsianOption::AsianOption(PayOff* _pay_off) : pay_off(_pay_off) {}

//====================
//AsianOptionArithmetic
//====================

AsianOptionArithmetic::AsianOptionArithmetic(PayOff* _pay_off) : AsianOption(_pay_off) {}

double AsianOptionArithmetic::pay_off_price(const std::vector<double>& spot_prices) const {
    unsigned num_times = spot_prices.size();
    double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), 0);
    double arith_mean = sum / static_cast<double>(num_times);

    return (*pay_off)(arith_mean);
}

//====================
//AsianOptionGeometric
//====================

AsianOptionGeometric::AsianOptionGeometric(PayOff* _pay_off) : AsianOption(_pay_off) {}

double AsianOptionGeometric::pay_off_price(const std::vector<double>& spot_prices) const {
    std::vector<double>::size_type num_times = spot_prices.size();
    double log_sum = 0.0;
    for (std::vector<double>::size_type i = 0; i < spot_prices.size(); i++) {
        log_sum += log(spot_prices[i]);
    }
    double geom_mean = exp(log_sum / static_cast<double>(num_times));

    return (*pay_off)(geom_mean);

}
#endif // ASIAN_CPP
