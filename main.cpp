#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>

// emulate libsodium RNG, valid for full 32bits result only!
static uint32_t randombytes_uniform(const uint32_t upper_bound) {
    static std::mt19937 mt{19876713};
    return mt();
}

// get 64bits from two 32bit numbers
static inline uint64_t rng() {
    return (uint64_t)randombytes_uniform(UINT32_MAX) << 32 | randombytes_uniform(UINT32_MAX);
}

const  int32_t bits_in_mantissa = 53;
const uint64_t max  = (1ULL << bits_in_mantissa);
const uint64_t mask = (1ULL << (bits_in_mantissa+1)) - 1;

static double rnd(double a, double b) {
    uint64_t r;
    do {
        r = rng() & mask; // get 54 random bits, need 53 or max
    } while (r > max);
    double v = ldexp( (double)r, -bits_in_mantissa ); // http://xoshiro.di.unimi.it/random_real.c
    return a + (b-a)*v;
}

int main() {
    double a = -3.5;
    double b = 3.5;

    int N = 10000000;

    double m = 0.0;
    for(int k = 0; k != N; ++k)
        // std::cout << rnd(a, b) << '\n';
        m += rnd(a, b);

    std::cout << m/N << '\n';

    return 0;
}
