#ifndef VANILLA_OPTION_CPP
#define VANILLA_OPTION_CPP

#include "vanilla_option.h"
#include <cmath>
#include "statistics.h"

//Init method initialise some member data --> Do-not Repeat Yourself (DRY)
void VanillaOption::init() {
   K = 100.0;
   r = 0.05;
   T = 1.0;
   S = 100.0;
   sigma = 0.2;
}

//Copies the member data
void VanillaOption::copy(const VanillaOption& rhs) {
    K = rhs.getK();
    r = rhs.getr();
    T = rhs.getT();
    S = rhs.getS();
    sigma = rhs.getsigma();
}

//Default constructor
VanillaOption::VanillaOption() { init(); }

//Parameter constructor
VanillaOption::VanillaOption(const double& _K, const double& _r,
                             const double& _T, const double& _S,
                             const double& _sigma) {
    K = _K;
    r = _r;
    T = _T;
    S = _S;
    sigma = _sigma;
}

// Copy constructor
VanillaOption::VanillaOption(const VanillaOption& rhs){
    copy(rhs);
}

//Assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& rhs){

    if (this == &rhs) return *this;

    copy(rhs);

    return *this;
}

//Destructor
VanillaOption::~VanillaOption(){}

//Accessors
double VanillaOption::getK() const {return K;}
double VanillaOption::getr() const {return r;}
double VanillaOption::getT() const {return T;}
double VanillaOption::getS() const {return S;}
double VanillaOption::getsigma() const {return sigma;}

//d1 and d2
double VanillaOption::calc_d1() const {
    return (log(S/K) + (r + sigma * sigma * 0.5) * T) / sigma * sqrt(T);
}

double VanillaOption::calc_d2() const {return calc_d1() - (sigma * sqrt(T)); }

//Payoff

double VanillaOption::calc_call_price() const {
    double d1 = calc_d1();
    double d2 = calc_d2();
    StandardNormalDistribution N;
    return S * N.cdf(d1) - K * exp(-r*T) * N.cdf(d2);

}

double VanillaOption::calc_put_price() const {
    double d1 = calc_d1();
    double d2 = calc_d2();
    StandardNormalDistribution N;
    return K * exp(-r*T) * N.cdf(-d2) - S * N.cdf(-d1);

}

#endif
