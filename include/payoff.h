#ifndef PAYOFF_H
#define PAYOFF_H

#include <algorithm>

class PayOff {
public:
    PayOff() {}; // Default (no parameter) constructor
    virtual ~PayOff() {}; // Virtual destructor

    //Overloaded operator(), turns the PayOff into an abstract function object
    virtual double operator() (const double S) const = 0; //pure virtual "=0"
};

// Payoff Call & Put

class PayOffCall : public PayOff {
    public:
        PayOffCall(const double _K); // No default constructor
        virtual ~PayOffCall() {}; //Destructor

        //Virtual function is now over_ridden (not pure-virtual anymore)
        virtual double operator() (const double S) const;  //Payoff is max(S-K;0)
    private:
        double K;
};

class PayOffPut : public PayOff {
    public:
        PayOffPut(const double _K); // No default constructor
        virtual ~PayOffPut() {}; //Destructor

        //Virtual function is now over_ridden (not pure-virtual anymore)
        virtual double operator() (const double S) const;  //Payoff is max(S-K;0)
    private:
        double K;
};

// Payoff double digital

class PayoffDoubleDigital : public PayOff {
    public:
        PayoffDoubleDigital(const double U_, const double D_);
        virtual ~PayoffDoubleDigital();

        //Payoff is 1 or zero
        virtual double operator() (const double S) const;

    private:
        double U;
        double D;
};


#endif // PAYOFF_H
