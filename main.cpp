#include "include/vanilla_option.h"
#include "include/black_scholes.h"
#include "include/payoff.h"
#include "include/Asian.h"
#include "include/Path_Generation.h"
#include "include/Linear_Congruential_Generator.h"
#include "include/statistics.h"

#include <iostream>
#include <Eigen/Dense>
#include <string>

//=====MC BS=======

/*int main(int argc, char **argv) {
    double S = 100.0;
    double K = 100.0;
    double r = 0.05;
    double v = 0.2;
    double T = 1.0;
    double delta_S = 0.001;
    double delta_v = 0.001;
    double delta_T = 0.001;
    double delta_r = 0.001;
    int num_sims = 100000000;



    double call = call_price(S, K, r, v, T);
    double call_delta_v = call_delta(S, K, r, v, T);
    double call_gamma_v = call_gamma(S, K, r, v, T);
    double call_vega_v = call_vega(S, K, r, v, T);
    double call_theta_v = call_theta(S, K, r, v, T);
    double call_rho_v = call_rho(S, K, r, v, T);


    double call_delta_f = delta_fdm(S, K, r, v, T, delta_S, "c");
    double call_gamma_f = gamma_fdm(S, K, r, v, T, delta_S, "c");

    double put = put_price(S, K, r, v, T);
    double put_delta_v = put_delta(S, K, r, v, T);
    double put_gamma_v = put_gamma(S, K, r, v, T);
    double put_vega_v = put_vega(S, K, r, v, T);
    double put_theta_v = put_theta(S, K, r, v, T);
    double put_rho_v = put_rho(S, K, r, v, T);

    double call_delta_m = delta_mc(num_sims, S, K, r, v, T, delta_S, "c");
    double call_gamma_m = gamma_mc(num_sims, S, K, r, v, T, delta_S, "c");

    std::cout << "Underlying:    " << S << std::endl;
    std::cout << "Strike:        " << K << std::endl;
    std::cout << "Rf:            " << r << std::endl;
    std::cout << "Volatility:    " << v << std::endl;
    std::cout << "Maturity:      " << T << std::endl;

    std::cout << "Call Price:    " << call << std::endl;
    std::cout << "Call Delta:    " << call_delta_v  << std::endl;
    std::cout << "Call Gamma:    " << call_gamma_v  << std::endl;
    std::cout << "Call Vega:    " << call_vega_v  << std::endl;
    std::cout << "Call Theta:    " << call_theta_v  << std::endl;
    std::cout << "Call Rho:    " << call_rho_v  << std::endl<< std::endl;

    std::cout << "Call delta fdm:    " << call_delta_f  << std::endl;
    std::cout << "Call gamma fdm:    " << call_gamma_f  << std::endl<< std::endl;

    std::cout << "Put Price:     " << put << std::endl;
    std::cout << "put Delta:    " << put_delta_v  << std::endl;
    std::cout << "put Gamma:    " << put_gamma_v  << std::endl;
    std::cout << "put Vega:    " << put_vega_v  << std::endl;
    std::cout << "put Theta:    " << put_theta_v  << std::endl;
    std::cout << "put Rho:    " << put_rho_v  << std::endl << std::endl;

    std::cout << "call delta mc:    " << call_delta_m  << std::endl;
    std::cout << "call gamma mc:    " << call_gamma_m  << std::endl;

    return 0;
}*/

//=====Asian=======

/*int main(int argc, char **argv) {
    unsigned num_sims = 100000;
    unsigned num_intervals = 250;
    double S = 30.0;
    double K = 29.0;
    double r = 0.08;
    double v = 0.3;
    double T = 1.00;
    std::vector<double> spot_prices(num_intervals, S);

    //Create the payoff object
    PayOff* pay_off_call = new PayOffCall(K);

    //Create the AsianOption object
    AsianOptionArithmetic asian(pay_off_call);

    //Update the spot price vector with correct spot price paths
    double payoff_sum = 0.0;
    for (int i=0; i<num_sims; i++) {
        calc_path_spot_prices(spot_prices, r, v, T);
        payoff_sum += asian.pay_off_price(spot_prices);
    }

    double discount_payoff_avg = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);

    delete pay_off_call;

    std::cout << "Number of Paths:    " << num_sims  << std::endl;
    std::cout << "Number of Inst:     " << num_intervals << std::endl;
    std::cout << "Underlying:         " << S << std::endl;
    std::cout << "Strike:             " << K << std::endl;
    std::cout << "Rf:                 " << r << std::endl;
    std::cout << "Volatility:         " << v << std::endl;
    std::cout << "Maturity:           " << T << std::endl << std::endl;
    std::cout << "Asian Price:        " << discount_payoff_avg << std::endl;

    return 0;
}*/

/*int main(int argc, char **argv) {
    double S = 100.0;
    double K = 100.0;
    double r = 0.05;
    double T = 1.00;
    double C_M = 10.5; //option market price

    //Create the BS call functor
    BlackScholesCall bsc(S, K, r, T);

    // Interval Bisection parameters
    double low_vol = 0.05;
    double high_vol = 0.35;
    double epsilon = 0.001;

    //calculate implied vol
    double sigma = interval_bisection<BlackScholesCall, &BlackScholesCall::option_price>
                    (C_M, low_vol, high_vol, epsilon, bsc);*/

    //Newton Raphson parameters
    /*double init = 0.3;
    double epsilon = 0.001;

    double sigma = newton_raphson<BlackScholesCall, &BlackScholesCall::option_price,
                    &BlackScholesCall::option_vega>
                    (C_M, init, epsilon, bsc);

    std::cout << "implied vol: " << sigma << std::endl;

    return 0;
}*/

/*int main (int argc, char **argv) {
    unsigned long init_seed = 1;
    unsigned long num_draws = 20;
    std::vector<double> random_draws(num_draws, 0.0);

    LinearCongruentialGenerator lgc(num_draws, init_seed);
    lgc.get_uniform_draws(random_draws);

    for (unsigned long i=0; i<num_draws; i++) {
        std::cout << random_draws[i] << std::endl;
    }

    return 0;


}*/

int main () {

StandardNormalDistribution snd;
std::vector<double> uniform_draws(20, 0.0);
std::vector<double> normal_draws(20, 0.0);



for (std::vector<double>::size_type i = 0; i<uniform_draws.size(); i++) {
    uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
}

snd.random_draws(uniform_draws, normal_draws);

for (std::vector<double>::size_type i = 0; i<normal_draws.size(); i++) {
    std::cout << normal_draws[i] << std::endl;
}


    return 0;


}
