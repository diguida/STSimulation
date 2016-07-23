#include "../include/LinearCongruentialGenerator.h"
#include "../include/MIDStub.h"
#include <cmath>
#include <iostream>

int main( int argc, char** argv ) {
  unsigned long long seed = 57;
  LinearCongruentialGenerator lcg( seed ), lcg2( seed );
  MIDStub< unsigned long long,
           LinearCongruentialGenerator::a,
           LinearCongruentialGenerator::c,
           LinearCongruentialGenerator::m > stub ( seed );
  double tau = 127.;
  double lambda = 1./tau;
  //first try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub.execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    lcg.random();
    lcg2.random();
    double r = lcg.random();
    double exp_r = - tau * std::log( r );
    double exp1_r = - tau * std::log( 1. - r );
    double exp_s = lcg2.exp( tau );
    std::cout << "Random exp_r: " << exp_r
              << ", exp_s: " << exp_s
              << ", exp1_r: " << exp1_r
              << std::endl;
  }
  
  //second try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub.execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
    lcg.random();
    lcg2.random();
    double r = lcg.random();
    double exp_r = - tau * std::log( r );
    double exp1_r = - tau * std::log( 1. - r );
    double exp_s = lcg2.exp( tau );
    std::cout << "Random exp_r: " << exp_r
              << ", exp_s: " << exp_s
              << ", exp1_r: " << exp1_r
              << std::endl;
  }
  /*
  //instantiating another stub the random number sequence continues
  MIDStub stub2;
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub2.execute( 127 );
    std::cout << "Stub execution time: " << t << std::endl;
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }

  //while with a new generator we restart from the beginning
  LinearCongruentialGenerator lcg2( MIDStub::seed );
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub2.execute( 127 );
    std::cout << "Stub execution time: " << t << std::endl;
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
    double exp_r2 = lcg2.exp( 127 );
    std::cout << "Random exp2: " << exp_r2 << std::endl;
  }

  //actually, we can use a static class methods...
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = MIDStub::execute( 127 );
    std::cout << "Stub execution time: " << t << std::endl;
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  */
  return 0;
}
