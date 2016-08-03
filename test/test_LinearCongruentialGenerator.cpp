#include "../include/LinearCongruentialGenerator.h"

#include <cmath>
#include <iostream>
#include <random>

using Pars = LinearCongruentialGeneratorParameters;

int main( int argc, char** argv ) {
  unsigned long long seed = 57;
  LinearCongruentialGenerator lcg( seed ), lcg2( seed );
  std::linear_congruential_engine< unsigned long long,
                                   Pars::a,
                                   Pars::c,
                                   Pars::m > lce( seed ),
                                             lce2( seed ), lce3( seed ), lce4( seed ),
                                             lce5( seed ), lce6( seed ), lce7( seed );
  std::uniform_real_distribution<> dis;
  for( unsigned int i = 0; i < 10; ++i ) {
    unsigned long long x = lce();
    double s = (double) x/lce.modulus;
    double r = lcg.random();
    double s2 = std::generate_canonical<double, 1>( lce2 );
    double s3 = std::generate_canonical<double, 32>( lce3 );
    double s4 = dis( lce4 );
     std::cout << "Random numbers: x = " << x
               << ", s = "<< s
               << ", r = " << r
               << ", s2 = " << s2
               << ", s3 = " << s3 
	       << ", s4 = " << s4 << std::endl;
  }
  double tau = 127.;
  double lambda = 1./tau;
  for( unsigned int i = 0; i < 10; ++i ) {
    std::exponential_distribution<> d( lambda );
    double exp_r = lcg2.exp( tau );
    double s5 = std::generate_canonical<double, 1>( lce5 );
    double exp_s5 = - tau * std::log( s5 );
    double exp1_s5 = - tau * std::log( 1. - s5 );
    double s6 = std::generate_canonical<double, 32>( lce6 );
    double exp_s6 = - tau * std::log( s6 );
    double exp1_s6 = - tau * std::log( 1. - s6 );
    double exp_s = d( lce7 );
    std::cout << "Random exp: exp_r = " << exp_r
              << ", exp_s5 = " << exp_s5
              << ", exp1_s5 = " << exp1_s5
              << ", exp_s6 = " << exp_s6
              << ", exp1_s6 = " << exp1_s6
              << ", exp_s = " << exp_s << std::endl;
  }
  return 0;
}
