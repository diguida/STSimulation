#include "../include/MIDTestDriver.h"
#include "../include/LinearCongruentialGenerator.h"

#include <functional>
#include <iostream>

using Pars = LinearCongruentialGeneratorParameters;

int main( int argc, char** argv ) {
  unsigned long long seed = 57;
  double tau = 127.;
  double lambda = 1./tau;
  using LCE = std::linear_congruential_engine< unsigned long long,
                                               Pars::a,
                                               Pars::c,
                                               Pars::m >;
  using MS = MIDStub< unsigned long long,
                      Pars::a,
                      Pars::c,
                      Pars::m >;
  using TD = MIDTestDriver< MS >;
  LCE lce{ seed };
  std::exponential_distribution<> d{ lambda };
  std::function<double()> rnd = std::bind( d, lce );
  std::shared_ptr<MS> p_stub = std::make_shared<MS>( seed );
  TD testDriver{ p_stub, lambda };
  // first try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    double exp_r = rnd();
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  //second try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
    double exp_r = rnd();
    std::cout << "Random exp: " << exp_r << std::endl;
  }

  // instantiating another test driver
  // from the same shared pointer
  // the random sequence continues
  std::cout << "*****" << std::endl;
  std::function<double()> rnd2 = std::bind( d, lce );
  TD testDriver2{ p_stub };
  testDriver2.lambda( lambda );
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver2.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
    double exp_r = rnd2();
    std::cout << "Wrong Random exp: " << exp_r << std::endl;
    exp_r = rnd();
    std::cout << "Right Random exp: " << exp_r << std::endl;
  }

  // instantiating another test driver
  // from another shared pointer
  // the random sequence re-starts
  std::cout << "*****" << std::endl;
  std::function<double()> rnd3 = std::bind( d, lce );
  TD testDriver3( std::make_shared<MS>( seed ) );
  testDriver3.lambda( lambda );
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver3.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
    double exp_r = rnd3();
    std::cout << "Random exp: " << exp_r << std::endl;
  }

  // now modifying lambda
  std::cout << "*****" << std::endl;
  double lambda4 = lambda;
  TD testDriver4( std::make_shared<MS>( seed ) );
  testDriver4.lambda( lambda4 );
  for( unsigned int i = 0; i < 10; ++i ) {
    std::cout << "Rate: " << testDriver4.lambda() << std::endl;
    double t = testDriver4.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
    std::exponential_distribution<> d( lambda4 );
    double exp_r = d( lce );
    std::cout << "Random exp: " << exp_r << std::endl;
    lambda4 /= 2.;
    testDriver4.lambda( lambda4 );
    std::cout << "Rate value set to: " << lambda4 << std::endl;
  }
  
  return 0;
}
