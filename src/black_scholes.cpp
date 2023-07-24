#include "black_scholes.h"

StandardNormalDistribution N;

BlackScholesCall::BlackScholesCall(double _S, double _K, double _r, double _T) :
    S(_S), K(_K), r(_r), T(_T) {}


double BlackScholesCall::option_price(double sigma) const {
    return call_price(S,K, r, sigma, T);
}

double BlackScholesCall::option_vega(double sigma) const {
    return call_vega(S, K, r, sigma, T);
}

BlackScholesPut::BlackScholesPut(double _S, double _K, double _r, double _T) :
    S(_S), K(_K), r(_r), T(_T) {}


double BlackScholesPut::option_price(double sigma) const {
    return put_price(S,K, r, sigma, T);
}

double BlackScholesPut::option_vega(double sigma) const {
    return put_vega(S, K, r, sigma, T);
}

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

double call_delta(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return N.cdf(d_j(1, S, K, r, v, T));
}

double put_delta(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return N.cdf(d_j(1, S, K, r, v, T)) - 1;
}

double call_gamma(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return N.pdf(d_j(1, S, K, r, v, T))/(S*v*sqrt(T));
}

double put_gamma(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {
    return N.pdf(d_j(1, S, K, r, v, T))/(S*v*sqrt(T));
}

double call_vega(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return S*N.pdf(d_j(1, S, K, r, v, T))*sqrt(T);
}

double put_vega(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return S*N.pdf(d_j(1, S, K, r, v, T))*sqrt(T);
}

double call_theta(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return -(S*N.pdf(d_j(1, S, K, r, v, T))*v)/(2*sqrt(T))
     - r*K*exp(-r*T)*N.cdf(d_j(2, S, K, r, v, T));
}

double put_theta(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return -(S*N.pdf(d_j(1, S, K, r, v, T))*v)/(2*sqrt(T))
     + r*K*exp(-r*T)*N.cdf(-d_j(2, S, K, r, v, T));
}


double call_rho(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return K*T*exp(-r*T)*N.cdf(d_j(2, S, K, r, v, T));
}

double put_rho(const double& S, const double& K, const double& r,
                  const double& v, const double& T) {

    return -K*T*exp(-r*T)*N.cdf(-d_j(2, S, K, r, v, T));
}

//FDM Greeks

double delta_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_S, string Opt) {

    if (Opt == "c") {
        return (call_price(S + delta_S, K, r, v, T) - call_price(S, K, r, v, T)) / delta_S;
    } else {
        return (put_price(S + delta_S, K, r, v, T) - put_price(S, K, r, v, T)) / delta_S;
    }

}


double gamma_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_S,
                  string Opt) {

    if (Opt == "c") {
        return (call_price(S + delta_S, K, r, v, T) - 2*call_price(S, K, r, v, T)
                + call_price(S - delta_S, K, r, v, T))/(delta_S*delta_S);
    } else {
        return (put_price(S + delta_S, K, r, v, T) - 2*put_price(S, K, r, v, T)
                + put_price(S - delta_S, K, r, v, T))/(delta_S*delta_S);
    }


}

double vega_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_v,
                  string Opt) {

    if (Opt == "c") {
        return (call_price(S, K, r, v + delta_v, T) - call_price(S, K, r, v, T)) / delta_v;
    } else {
        return (put_price(S, K, r, v + delta_v, T) - put_price(S, K, r, v, T)) / delta_v;
    }
}

double theta_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_T,
                  string Opt) {

    if (Opt == "c") {
        return (call_price(S, K, r, v, T + delta_T) - call_price(S, K, r, v, T)) / delta_T;
    } else {
        return (put_price(S, K, r, v, T + delta_T) - put_price(S, K, r, v, T)) / delta_T;
    }

}

double rho_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_r,
                  string Opt) {

    if (Opt == "c") {
        return (call_price(S, K, r + delta_r, v, T) - call_price(S, K, r, v, T)) / delta_r;
    } else {
        return (put_price(S, K, r + delta_r, v, T) - put_price(S, K, r, v, T)) / delta_r;
    }

}


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


void monte_carlo_option_price(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, double& price_Sp,
                              double& price_S, double& price_Sm, string Opt) {

    //3 separated paths for each increment/decrement
    double Sp_adjust = (S+delta_S) * exp(T*(r-0.5*v*v));
    double S_adjust = S * exp(T*(r-0.5*v*v));
    double Sm_adjust = (S-delta_S) * exp(T*(r-0.5*v*v));

    //current prices stored
    double Sp_cur = 0.0;
    double S_cur = 0.0;
    double Sm_cur = 0.0;

    // 3 different payoff
    double payoff_sum_p = 0.0;
    double payoff_sum = 0.0;
    double payoff_sum_m = 0.0;

    //Loop over the number of simulations
    for (int i=0; i<num_sims; i++) {
        double gauss_bm = gaussian_box_muller();

        //adjust the paths
        double expgauss = exp(sqrt(v*v*T)*gauss_bm);
        Sp_cur = Sp_adjust * expgauss;
        S_cur = S_adjust * expgauss;
        Sm_cur = Sm_adjust * expgauss;

        //payoffs
        if (Opt=="c") {
            payoff_sum_p += std::max(Sp_cur - K, 0.0);
            payoff_sum += std::max(S_cur - K, 0.0);
            payoff_sum_m += std::max(Sm_cur - K, 0.0);
        } else {
            payoff_sum_p += std::max(K - Sp_cur, 0.0);
            payoff_sum += std::max(K - S_cur, 0.0);
            payoff_sum_m += std::max(K - Sm_cur, 0.0);
        }

    }

    //payoff actualization
    price_Sp = (payoff_sum_p / static_cast<double>(num_sims)) * exp(-r*T);
    price_S = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
    price_Sm = (payoff_sum_m / static_cast<double>(num_sims)) * exp(-r*T);

}

double delta_mc(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, string Opt){

    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    monte_carlo_option_price(num_sims, S, K, r, v, T, delta_S, price_Sp,
                             price_S, price_Sm, Opt);

    return (price_Sp-price_S)/delta_S;
}

double gamma_mc(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, string Opt) {

    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    monte_carlo_option_price(num_sims, S, K, r, v, T, delta_S, price_Sp,
                             price_S, price_Sm, Opt);


    return (price_Sp - 2*price_S + price_Sm)/(delta_S*delta_S);
}



