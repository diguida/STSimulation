#include "../include/MIDStub.h"
#include <iostream>

int main( int argc, char** argv ) {
  MIDStub stub;
  LinearCongruentialGenerator lcg( MIDStub::seed );
  //first try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub.execute( 127 );
    std::cout << "Stub execution time: " << t << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  //second try
  for( unsigned int i = 0; i < 10; ++i ) {
    double t = stub.execute( 127 );
    std::cout << "Stub execution time: " << t << std::endl;
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }

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

  return 0;
}
