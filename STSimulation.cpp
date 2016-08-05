#include "include/LinearCongruentialGeneratorParameters.h"
#include "include/MIDTestDriver.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Pars = LinearCongruentialGeneratorParameters;
using MS = MIDStub< unsigned long long,
                    Pars::a,
                    Pars::c,
                    Pars::m >;
using TD = MIDTestDriver< MS >;

template< class T >
static void vectorDump( T const & vec, std::string const & delimiter, std::string& dump ) {
  std::ostringstream ss;
  std::for_each( vec.cbegin(), vec.cend() - 1
               , [ &ss, &delimiter ]( typename T::value_type const & d ){ ss << d;
                                                                          ss << delimiter;
                                                                          }
                 );
  ss << *vec.crbegin();
  dump += std::string( "[" );
  dump += ss.str();
  dump += std::string( "]" );
}

int main( int argc, char** argv ) {
  // Part 0: Input values:
  // * seed for the generator,
  // * number of initial faults,
  // * (constant) failure rate in the pre-run phase (failure/h),
  // * number of failures to be observed in the pre-run phase,
  // * number of failures to be observed in the run phase.
  // * Musa factor A.
  unsigned long long seed; //57245;
  unsigned int initialFaults; //60;
  double lambda_preRun; //0.00785; //failures per hour
  std::size_t observations_preRun; //100;
  std::size_t observations; //50;
  double musaFactor; //0.95;
  std::cout << "Enter seed: ";
  std::cin >> seed;
  std::cout << "Enter the number of initial faults: ";
  std::cin >> initialFaults;
  std::cout << "Enter the (constant) failure rate in the pre-run phase (failure/h): ";
  std::cin >> lambda_preRun;
  std::cout << "Enter the number of failures to be observed in the pre-run phase: ";
  std::cin >> observations_preRun;
  std::cout << "Enter the number of failures to be observed in the run phase: ";
  std::cin >> observations;
  std::cout << "Enter the Musa factor A: ";
  std::cin >> musaFactor;

  // Part 1: The set up of the simulation:
  // * definition of the Linear Congruential Generator:
  //   We use the modulus, the multiplier, and the increment as declared
  //   in the utility class LinearCongruentialGeneratorParameters,
  //   then we set the seed at runtime;
  // * instantiation of the test stub:
  //   we use it as a service, and we enforce this
  //   by using the shared pointer interface;
  // * creation of the output file: it contains the seed and the number of
  //   pre-run and run iterations in the name.
  // * first bunch of generation of random numbers, in order to
  //   reduce the dependency of the sequence from the seed.
  constexpr unsigned int setupGenerations = 100000;
  std::shared_ptr<MS> p_stub = std::make_shared<MS>( seed );
  std::cout << "************************ GENERATOR ************************\n"
            << "* Modulus: " << Pars::m << "\n"
            << "* Multiplier: " << Pars::a << "\n"
            << "* Increment: " << Pars::c << "\n"
            << "* Input seed: " << seed << "\n"
            << "***********************************************************"
            << std::endl;
  std::ostringstream fileNameSS;
  fileNameSS << std::string( "STResults" )
             << std::string( "_" ) << std::string( "seed" ) << seed
             << std::string( "_" ) << std::string( "faults" ) << initialFaults
             << std::string( "_" ) << std::string( "failrate" ) << lambda_preRun
             << std::string( "_" ) << std::string( "prerun" ) << observations_preRun
             << std::string( "_" ) << std::string( "run" ) << observations
             << std::string( "_" ) << std::string( "A" ) << musaFactor
             << std::string( ".txt" );
  for(unsigned int i = 0; i < setupGenerations; ++i)
    p_stub->execute( 1. );

  // Part 2: The pre-run phase:
  // * instantiation of the test driver:
  //   it will use the shared stub
  //   to generate random numbers from the same sequence;
  // * the number of initial defects is initialFaults;
  // * the lifetime has an exponential distribution with fixed rate lambda_preRun;
  // * the number of failure to be observed is observations_preRun;
  //   this is the number of random interfailure times
  //   to be produced iteratively via the test driver.
  TD testDriver_preRun{ p_stub, lambda_preRun };
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
    preRunTime += t;
    std::cout << "Inter-failure time between failure " << i
              << " and " << i + 1
              << " in the pre-run phase: " << t << std::endl;
    std::cout << "Time spent in executing the MID till failure " << i + 1
              << ": " << preRunTime << std::endl;
  }

  // Part 3: The computation of the rate of failure per faults:
  // ratio between the number of observed failure in the pre-run phase
  // and the product of the initial faults and the time spent in the pre-run
  // phi_0 = observations_preRun / ( initialFaults * preRunTime )
  double phi_0 = (double) observations_preRun / ( initialFaults * preRunTime );
  std::cout << "********************* PRE-RUN RESULTS *********************\n"
            << "* Total time spent in the pre-run phase: " << preRunTime << " h\n"
            << "* Inizial rate of failure per faults: " << phi_0 << " failures/(h*fault)\n"
            << "***********************************************************"
            << std::endl;
  
  // Part 4: The run phase:
  // * instantiation of the test driver:
  //   it will use the shared stub
  //   to generate random numbers from the same sequence;
  // * the rate of failure per faults is phi_0, obtained in the pre-run phase;
  // * the number of initial defects is initialFaults;
  // * the Musa factor musaFactor:
  //   it is the product of the fault reduction factor at infinite time
  //   and the testing compression factor;
  // * the rate of the exponential distribution:
  //   lambda = phi_0 * initialFaults * exp( -phi_0 * musaFactor * t_i )
  //   depends from the failure times t_i, so it will change after every failure;
  // * the number of failure to be observed is observations;
  //   this is the number of random interfailure times
  //   to be produced iteratively via the test driver.
  double runTime = 0.;
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
            << "* Number of failures to be observed: " << observations <<"\n"
            << "***********************************************************"
            << std::endl;
  TD testDriver{ p_stub };
  for( std::size_t i = 0; i < observations; ++i ) {
    double lambda =  phi_0 * initialFaults * std::exp( -phi_0 * musaFactor * runTime );
    testDriver.lambda( lambda );
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

  // Part 5: The output:
  // We create one file containing the lifetimes and the failure instants.
  std::string dumpInterfailureTimes, dumpFailureTimes;
  vectorDump( interfailureTimes, std::string( ", " ), dumpInterfailureTimes );
  vectorDump( failureTimes, std::string( ", " ), dumpFailureTimes );
  std::cout << "*********************** RUN RESULTS ***********************\n"
            << "* Inter-failure times: " << dumpInterfailureTimes << "\n"
            << "* Failure times: " << dumpFailureTimes << "\n"
            << "***********************************************************"
            << std::endl;
  std::ofstream ofs( fileNameSS.str() );
  ofs << "N0 = " << initialFaults << ";\n"
      << "phi0 = " << phi_0 << ";\n"
      << "A = " << musaFactor << ";\n"
      << "T = List" << dumpInterfailureTimes << ";\n"
      << "t = List" << dumpFailureTimes << ";";
  ofs.close();
  return 0;
}
