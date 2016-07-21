#ifndef include_LinearCongruentialGenerator_h
#define include_LinearCongruentialGenerator_h

#include <cmath>

class LinearCongruentialGenerator {
public:
  static constexpr unsigned long long m = 2147483648; //the modulus is set to 2^31
  //static constexpr double inverse_m = (double) 1/m;
  // the value of the multiplier guarantees maximum period
  // and allows to pass tests for randomness.
  static constexpr unsigned long long a = 1220703125;
  static constexpr unsigned long long c = 0; // increment set to 0, so multiplicative method

  LinearCongruentialGenerator( unsigned long long seed );

  unsigned long long getSeed() const;

  double random(); 

  double exp( double tau );

private:
  // the initial seed is kept as a reference
  unsigned long long m_seed;
  // the value of last generated random number must be kept:
  // it will be used to generate the next one in the linear formula
  unsigned long long m_x;
};

#endif
