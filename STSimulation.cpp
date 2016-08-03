#include <iostream>
#include <vector>

#include "include/LinearCongruentialGeneratorParameters.h"
#include "include/MIDTestDriver.h"

using Pars = LinearCongruentialGeneratorParameters;
using MS = MIDStub< unsigned long long,
                    Pars::a,
                    Pars::c,
                    Pars::m >;
using TD = MIDTestDriver< unsigned long long,
                          Pars::a,
                          Pars::c,
                          Pars::m >;

int main(  int argc, char** argv ) {
  // Part 1: set up of the simulation:
  // * definition of the Linear Congruential Generator:
  //   We use the modulus, the multiplier, and the increment as
  //   declared in the utility class LinearCongruentialGeneratorParameters,
  //   then we set the seed
  // * instantiation of the test stub: we use it as a service, and we enforce this by using the shared pointer interface;
  // * instantiation of the test driver: it will use the shared stub to generate random numbers from the same sequence.
  unsigned long long seed = 57;
  std::shared_ptr<MS> p_stub = std::make_shared<MS>( seed );
  TD testDriver{ p_stub };

  // Part 2: The pre-run phase:
  // * the number of initial defects is initial_faults;
  // * the number of failure to be observed is observations_pre_run; this is the number of random interfailure times to be produced iteratively via the test driver.
  // * the lifetime has an exponential distribution with fixed rate lambda_pre_run;
  unsigned int initialFaults = 60;
  std::size_t observations_preRun = 100;
  std::vector<double> interfailureTimes_preRun;
  interfailureTimes_preRun.reserve( observations_preRun );
  double lambda_preRun = 0.00785; //failures per hour
  testDriver.setRate( lambda_preRun );
  double time_preRun = 0.;
  for( std::size_t i = 0; i < observations_preRun; ++i ) {
    std::cout << "Testing the MID: looking for failure " << i << std::endl;
    double t = testDriver.callMID();
    interfailureTimes_preRun.push_back( t );
    time_preRun += t;
    std::cout << "Inter-failure time in the pre-run phase: " << t << std::endl;
  }
  std::cout << "Total time spent in the pre-run phase: " << time_preRun << " hours." << std::endl;
  return 0;
}
