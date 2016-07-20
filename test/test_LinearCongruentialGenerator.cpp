#include "../include/LinearCongruentialGenerator.h"
#include <iostream>

int main( int argc, char** argv ) {
  LinearCongruentialGenerator lcg( 57 );
  for( unsigned int i = 0; i < 10; ++i ) {
    double r = lcg.random();
    std::cout << "Random number: " << r << std::endl;
  }
  for( unsigned int i = 0; i < 10; ++i ) {
    double exp_r = lcg.exp( 127 );
    std::cout << "Random exp: " << exp_r << std::endl;
  }
  return 0;
}
