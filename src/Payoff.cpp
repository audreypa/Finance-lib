#ifndef PAYOFF_CPP
#define PAYOFF_CPP
#include "payoff.h"

// payoff call
PayOffCall::PayOffCall(const double _K) {K = _K; }


// Over-ridden operator() --> functor
double PayOffCall::operator()(const double S) const {
    return std::max(S-K, 0.0);
}

// payoff put

PayOffPut::PayOffPut(const double _K) {K = _K; }


// Over-ridden operator() --> functor
double PayOffPut::operator()(const double S) const {
    return std::max(K-S, 0.0);
}


// Payoffdigital
PayoffDoubleDigital::PayoffDoubleDigital(const double _U, const double _D)
{
    U=_U;
    D=_D;
}

PayoffDoubleDigital::~PayoffDoubleDigital() {}

//Operator()

double PayoffDoubleDigital::operator()(const double S) const {
    if (S >= D && S <= U){
        return 1.0;
    } else {
        return 0.0;
    }
}

#endif
