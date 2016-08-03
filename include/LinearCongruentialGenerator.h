#ifndef include_LinearCongruentialGenerator_h
#define include_LinearCongruentialGenerator_h

#include "LinearCongruentialGeneratorParameters.h"
#include <cmath>

class LinearCongruentialGenerator {
public:
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
