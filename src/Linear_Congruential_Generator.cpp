#ifndef LINEAR_CONGRUENTIAL_GENERATOR_CPP
#define LINEAR_CONGRUENTIAL_GENERATOR_CPP

#include "Linear_Congruential_Generator.h"

const unsigned long a = 16807;
const unsigned long m = 2147483647;

//Scharge's algo constants

const unsigned long q = 12773;
const unsigned long r = 2836;

//Parameter constructor

LinearCongruentialGenerator::LinearCongruentialGenerator(
            unsigned long _num_draws,
            unsigned long _init_seed) : RandomNumberGenerator(_num_draws,_init_seed) {

    if (_init_seed == 0) {
        init_seed = 1;
        cur_seed = 1;
    }

    max_multiplier = 1.0 / (1.0 + (m-1));
}

//Obtains a number unsigned long integer

unsigned long LinearCongruentialGenerator::get_random_integer() {
    unsigned long k = 0;
    k = cur_seed / q;
    cur_seed = a * (cur_seed - k * q) - r * k;

    if (cur_seed < 0) {
        cur_seed += m;
    }

    return cur_seed;
}

//Create a vector of uniform draws between (0,1)

void LinearCongruentialGenerator::get_uniform_draws(std::vector<double>& draws) {
    for (unsigned long i=0; i<num_draws; i++) {
        draws[i] = get_random_integer() * max_multiplier;
    }
}
#endif // LINEAR_CONGRUENTIAL_GENERATOR_CPP
