#include <iostream>
#include <vector>

#include "include/LinearCongruentialGeneratorParameters.h"
#include "include/MIDTestDriver.h"

using Pars = LinearCongruentialGeneratorParameters;
using MS = MIDStub< unsigned long long,
                    Pars::a,
                    Pars::c,
                    Pars::m >;
using TD = MIDTestDriver< MS >;

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
  TD testDriver_preRun{ p_stub };
  testDriver_preRun.setRate( lambda_preRun );
  std::cout << "********************** PRE-RUN PHASE **********************\n"
            << "* Number of initial faults: " << initialFaults << "\n"
            << "* Initial (constant) rate of failures: " << lambda_preRun << " failures/h\n"
            << "* Number of failures to be observed: " << observations_preRun <<"\n"
            << "***********************************************************"
            << std::endl;
  double preRunTime = 0.;
  for( std::size_t i = 0; i < observations_preRun; ++i ) {
    std::cout << "Testing the MID: running up to failure " << i + 1 << std::endl;
    double t = testDriver_preRun.callMID();
    interfailureTimes_preRun.push_back( t );
    preRunTime += t;
    std::cout << "Inter-failure time between failure " << i
              << " and " << i + 1
              << " in the pre-run phase: " << t << std::endl;
    std::cout << "Time spent in executing the MID till failure " << i + 1
              << ": " << preRunTime << std::endl;
  }
  std::cout << "Total time spent in the pre-run phase: " << preRunTime << " hours." << std::endl;

  // Part 3: Extracting the rate of failure per faults:
  // ratio between the number of observed failure in the pre-run phase
  // and the product of the initial faults and the time spent in the pre-run
  // phi_0 = observations_preRun / ( initialFaults * preRunTime )
  double phi_0 = (double) observations_preRun / ( initialFaults * preRunTime );
  std::cout << "********************* PRE-RUN RESULTS *********************\n"
            << "* Total time spent in the pre-run phase: " << preRunTime << " h\n"
            << "* Inizial rate of failure per faults: " << phi_0 << " failures/(h*fault)\n"
            << "***********************************************************"
            << std::endl;
  
  // Part 4: The run phase
  // * the rate of failure per faults is phi_0, obtained in the pre-run phase;
  // * the number of initial defects is initialFaults;
  // * the Musa factor musaFactor is the product of the fault reduction factor at infinite time and the testing compression factor;
  // * the rate of the exponential distribution lambda = phi_0 * initialFaults * exp( -phi_0 * musaFactor * t_i ) depends from the failure times t_i, so it will change after every failure;
  // * the number of failure to be observed is observations; this is the number of random interfailure times to be produced iteratively via the test driver.
  double musaFactor = 0.95;
  double runTime = 0.;
  std::size_t observations = 50;
  std::vector<double> interfailureTimes, failureTimes;
  interfailureTimes.reserve( observations );
  // we reserve an element more in the vector of the failure times
  // as the first element is t_0 = 0;
  failureTimes.reserve( observations + 1 );
  failureTimes.push_back( runTime );
  std::cout << "************************ RUN PHASE ************************\n"
            << "* Number of initial faults: " << initialFaults << "\n"
            << "* Musa factor: " << musaFactor << "\n"
            << "* Initial rate of failures: " << phi_0 * initialFaults << " failures/h\n"
            << "* Number of failures to be observed: " << observations_preRun <<"\n"
            << "***********************************************************"
            << std::endl;
  TD testDriver{ p_stub };
  for( std::size_t i = 0; i < observations; ++i ) {
    double lambda =  phi_0 * initialFaults * std::exp( -phi_0 * musaFactor * runTime );
    testDriver.setRate( lambda );
    std::cout << "Testing the MID: running up to failure " << i + 1
              << " with failure rate " << lambda << " failures/h" << std::endl;
    double t = testDriver.callMID();
    interfailureTimes.push_back( t );
    runTime += t;
    failureTimes.push_back( runTime );
    std::cout << "Inter-failure time between failure " << i
              << " and " << i + 1
              << " in the run phase: " << t << std::endl;
    std::cout << "Time spent in executing the MID till failure " << i + 1
              << ": " << runTime << std::endl;
  }

  return 0;
}
