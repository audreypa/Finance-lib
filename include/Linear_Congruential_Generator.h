#ifndef LINEAR_CONGRUENTIAL_GENERATOR_H
#define LINEAR_CONGRUENTIAL_GENERATOR_H

#include "Random.h"

class LinearCongruentialGenerator : public RandomNumberGenerator {
private:
    double max_multiplier;

public:
    LinearCongruentialGenerator(unsigned long _num_draws,unsigned long _init_seed=1);

    virtual ~LinearCongruentialGenerator() {};

    virtual unsigned long get_random_integer();
    virtual void get_uniform_draws(std::vector<double>& draws);
};


#endif // LINEAR_CONGRUENTIAL_GENERATOR_H
