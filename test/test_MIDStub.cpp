#include "../include/LinearCongruentialGenerator.h"
#include "../include/MIDStub.h"

#include <cmath>
#include <iostream>
#include <memory>

using Pars = LinearCongruentialGeneratorParameters;

int main( int argc, char** argv ) {
  unsigned long long seed = 57;
  LinearCongruentialGenerator lcg( seed ), lcg1( seed ), lcg2( seed ), lcg3( seed );
  using MS = MIDStub< unsigned long long,
                      Pars::a,
                      Pars::c,
                      Pars::m >;
  std::shared_ptr<MS> p_stub = std::make_shared<MS>( seed );
  double tau = 127.;
  double lambda = 1./tau;
  //first try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = p_stub->execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    lcg.random();
    lcg1.random();
    double r = lcg.random();
    double exp_r = - tau * std::log( r );
    double exp1_r = - tau * std::log( 1. - r );
    double exp_s = lcg1.exp( tau );
    std::cout << "Random exp_r: " << exp_r
              << ", exp_s: " << exp_s
              << ", exp1_r: " << exp1_r
              << std::endl;
  }
  
  //second try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = p_stub->execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
    lcg.random();
    lcg1.random();
    double r = lcg.random();
    double exp_r = - tau * std::log( r );
    double exp1_r = - tau * std::log( 1. - r );
    double exp_s = lcg1.exp( tau );
    std::cout << "Random exp_r: " << exp_r
              << ", exp_s: " << exp_s
              << ", exp1_r: " << exp1_r
              << std::endl;
  }

  // instantiating another stub
  // by copy constructing the shared pointer:
  // the random number sequence continues
  std::shared_ptr<MS> p_stub2 = p_stub;
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = p_stub2->execute( lambda );
    std::cout << "Second stub execution time: " << t << std::endl;
    lcg.random();
    lcg1.random();
    double exp1_r = - tau * std::log( 1. - lcg.random() );
    lcg1.random();
    std::cout << "First random exp: " << exp1_r << std::endl;
    lcg2.random();
    exp1_r = - tau * std::log( 1. - lcg2.random() );
    std::cout << "Second random exp: " << exp1_r << std::endl;
    t = p_stub->execute( lambda );
    std::cout << "First stub execution time: " << t << std::endl;
    lcg.random();
    lcg1.random();
    exp1_r = - tau * std::log( 1. - lcg.random() );
    lcg1.random();
    std::cout << "First random exp: " << exp1_r << std::endl;
    lcg2.random();
    exp1_r = - tau * std::log( 1. - lcg2.random() );
    std::cout << "Second random exp: " << exp1_r << std::endl;
  }

  // while with a new stub, allocated statically,
  // we restart the random sequence from the beginning
  MS stub3( seed );
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub3.execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
    lcg3.random();
    double exp1_r = - tau * std::log( 1. - lcg3.random() );
    std::cout << "Random exp: " << exp1_r << std::endl;
  }
  // the copy preserves the random sequence
  MS stub4 = stub3;
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub4.execute( lambda );
    std::cout << "Stub execution time: " << t << std::endl;
    lcg3.random();
    double exp1_r = - tau * std::log( 1. - lcg3.random() );
    std::cout << "Random exp: " << exp1_r << std::endl;
  }

  return 0;
}
