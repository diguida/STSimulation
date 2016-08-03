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
  std::cout << "************************ GENERATOR ************************\n"
            << "* Modulus: " << Pars::m << "\n"
            << "* Multiplier: " << Pars::a << "\n"
            << "* Increment: " << Pars::c << "\n"
            << "* Input seed: " << seed << "\n"
            << "***********************************************************"
            << std::endl;

  // Part 2: The pre-run phase:
  // * the number of initial defects is initialFaults;
  // * the lifetime has an exponential distribution with fixed rate lambda_preRun;
  // * the number of failure to be observed is observations_preRun; this is the number of random interfailure times to be produced iteratively via the test driver.
  unsigned int initialFaults = 60;
  double lambda_preRun = 0.00785; //failures per hour
  std::size_t observations_preRun = 100;
  std::vector<double> interfailureTimes_preRun;
  interfailureTimes_preRun.reserve( observations_preRun );
  testDriver.setRate( lambda_preRun );
  std::cout << "********************** PRE-RUN PHASE **********************\n"
            << "* Number of initial faults: " << initialFaults << "\n"
            << "* Initial (constant) rate of failures: " << lambda_preRun << " failures/h\n"
            << "* Number of failures to be observed: " << observations_preRun <<"\n"
            << "***********************************************************"
            << std::endl;
  double time_preRun = 0.;
  for( std::size_t i = 0; i < observations_preRun; ++i ) {
    std::cout << "Testing the MID: running up to failure " << i + 1 << std::endl;
    double t = testDriver.callMID();
    interfailureTimes_preRun.push_back( t );
    time_preRun += t;
    std::cout << "Inter-failure time between failure " << i
              << " and " << i + 1
              << " in the pre-run phase: " << t << std::endl;
    std::cout << "Time spent in executing the MID till failure " << i + 1
              << ": " << time_preRun << std::endl;
  }
  std::cout << "Total time spent in the pre-run phase: " << time_preRun << " hours." << std::endl;
  // Part 3: Extracting the rate of failure per faults:
  // ratio between the number of observed failure in the pre-run phase
  // and the product of the initial faults and the time spent in the pre-run
  // phi_0 = observations_preRun / ( initialFaults * time_preRun )
  double phi_0 = (double) observations_preRun / ( initialFaults * time_preRun );
  std::cout << "********************* PRE-RUN RESULTS *********************\n"
            << "* Total time spent in the pre-run phase: " << time_preRun << " h\n"
            << "* Inizial rate of failure per faults: " << phi_0 << " failures/(h*fault)\n"
            << "***********************************************************"
            << std::endl;
  
  // Part 4: The run phase
  // * the number of initial defects is initialFaults;
  // * the number of failure to be observed is observations; this is the number of random interfailure times to be produced iteratively via the test driver;
  // * the rate of failure per faults is phi_0, obtained in the pre-run phase // 
  return 0;
}
