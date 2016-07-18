#include "../include/LinearCongruentialGenerator.h"

LinearCongruentialGenerator::LinearCongruentialGenerator( unsigned long long seed ):
  m_seed( seed ) {}

double LinearCongruentialGenerator::random() {
  //Produces uniformly-distributed floating points between 0 and 1.
  m_seed = ( a * m_seed ) % m;
  double r = (double) m_seed/m;
  return r;
}

double LinearCongruentialGenerator::exp( double tau ) {
  // Returns an exponential distribution exp( -t/tau )
  double x = this->random(); // uniform on [ 0, 1 [
  double t = -tau * std::log( x ); // convert to exponential distribution
  return t;
}
