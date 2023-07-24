#ifndef BLACK_SCHOLES_H_INCLUDED
#define BLACK_SCHOLES_H_INCLUDED
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>
#include "statistics.h"

using std::string;

//===============
//ANALYTIC FORMULAE
//===============

class BlackScholesCall {
private:
    double S;
    double K;
    double r;
    double T;

public:
    BlackScholesCall(double _S, double _K, double _r, double _T);
    double option_price(double sigma) const;
    double option_vega(double sigma) const;

};

class BlackScholesPut {
private:
    double S;
    double K;
    double r;
    double T;

public:
    BlackScholesPut(double _S, double _K, double _r, double _T);
    double option_price(double sigma) const;
    double option_vega(double sigma) const;

};

double d_j(const int& j, const double& S, const double& K, const double& r,
           const double& v, const double& T);

double call_price(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_price(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double call_delta(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_delta(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double call_gamma(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_gamma(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double call_vega(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_vega(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double call_theta(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_theta(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double call_rho(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_rho(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

//FDM Greeks

double delta_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_S, string Opt);

double gamma_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_S,
                  string Opt);

double vega_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_v,
                  string Opt);

double theta_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_T,
                  string Opt);

double rho_fdm(const double& S, const double& K, const double& r,
                  const double& v, const double& T, const double& delta_r,
                  string Opt);




double gaussian_box_muller();

//Pricing Option with MC method and three increments (up, neutral, down)

void monte_carlo_option_price(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, double& price_Sp,
                              double& price_S, double& price_Sm, string Opt);

double delta_mc(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, string Opt);


double gamma_mc(const int num_sims, const double S, const double K, const double r,
                              const double v, const double T, const double delta_S, string Opt);

//Implied Volatility Algorithms

//**Interval Bisection**

template<typename T, double(T::*g)(double) const>
double interval_bisection(double y_target, double m, double n, double epsilon, T& root_func){

    double x = 0.5 * (m + n);
    double y = (root_func.*g)(x);

    do {
        if (y < y_target) {
            m = x;
        }

        if (y > y_target) {
            n = x;
        }

        x = 0.5 * (m + n);
        y = (root_func.*g)(x);
    } while (fabs(y-y_target) > epsilon);

    return x;
}

//**Newton-Raphson**

template<typename T, double(T::*g)(double) const,
                     double(T::*g_prime)(double) const>
double newton_raphson(double y_target, double init, double epsilon,
                      const T& root_func) {


    double y = (root_func.*g)(init);
    double x = init;

    while (fabs(y-y_target) > epsilon) {
        double d_x = (root_func.*g_prime)(x);
        x += (y_target - y)/d_x;
        y = (root_func.*g)(x);
    }
    return x;
}

#endif // BLACK_SCHOLES_H_INCLUDED
