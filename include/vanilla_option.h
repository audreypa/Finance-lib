#ifndef VANILLA_OPTION_H
#define VANILLA_OPTION_H

class VanillaOption
{
    private:
        void init();
        void copy(const VanillaOption& rhs); //rhs is "right hand side" and pass-by-ref-to-const method

        double K;
        double r;
        double T;
        double S;
        double sigma;

    public:
        VanillaOption(); //default constructor
        VanillaOption(const double& _K, const double& _r,
                      const double& _T, const double& _S,
                      const double& _sigma); //parameter constructor. const at the beginning means return a constant which cannot be modified anymore
        VanillaOption(const VanillaOption& rhs); // Copy constructor
        VanillaOption& operator=(const VanillaOption& rhs); //Assignment operator
        virtual ~VanillaOption(); //Destructor

        //Selector ("getter") methods for option parameters
        double getK() const; //note that const at the end means the method is unable to modify member data
        double getr() const;
        double getT() const;
        double getS() const;
        double getsigma() const;

        //Option payoff
        double calc_d1() const;
        double calc_d2() const;
        double calc_call_price() const;
        double calc_put_price() const;

};

#endif // VANILLA_OPTION_H
