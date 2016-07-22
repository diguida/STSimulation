#include "../include/MIDTestDriver.h"
#include "../include/MIDStub.h"
#include "../include/LinearCongruentialGenerator.h"
#include <iostream>

int main( int argc, char** argv ) {
  MIDTestDriver testDriver( 127. );
  LinearCongruentialGenerator lcg( MIDStub::seed );
  // first try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  //second try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = testDriver.callMID();
    std::cout << "Driver inter-failure time: " << t << std::endl;
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  return 0;
}
