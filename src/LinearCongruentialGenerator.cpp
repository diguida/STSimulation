#include "../include/LinearCongruentialGenerator.h"
#if DEBUG
#include <iostream>
#endif

LinearCongruentialGenerator::LinearCongruentialGenerator( unsigned long long seed ):
  m_seed( seed ),
  m_x( seed ) {}

unsigned long long LinearCongruentialGenerator::getSeed() const {
  return m_seed;
}

double LinearCongruentialGenerator::random() {
  //Produces uniformly-distributed floating points between 0 and 1.
#if DEBUG
  std::cout << "[LinearCongruentialGenerator::random] starting value = " << m_x << ", ";
#endif
  m_x = ( a * m_x ) % m;
  double r = (double) m_x/m;
#if DEBUG
  std::cout << "x = " << m_x << ", r = " << r << std::endl;
#endif
  return r;
}

double LinearCongruentialGenerator::exp( double tau ) {
  // Returns an exponential distribution exp( -t/tau )
#if DEBUG
  std::cout << "[LinearCongruentialGenerator::exp] starting value before the random call = " << m_x << std::endl;
#endif
  double r = this->random(); // uniform on [ 0, 1 [
  double t = -tau * std::log( r ); // convert to exponential distribution
#if DEBUG
  std::cout << "[LinearCongruentialGenerator::exp] tau = " << tau << ", t = " << t << std::endl;
  std::cout << "[LinearCongruentialGenerator::exp] starting value after the random call = "  << m_x << std::endl;
#endif
  return t;
}
