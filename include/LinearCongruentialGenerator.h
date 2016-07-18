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

  double random(); 

  double exp( double tau );

private:
  unsigned long long m_seed;
};

#endif
