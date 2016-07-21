#ifndef include_MIDStub_h
#define include_MIDStub_h

#include "LinearCongruentialGenerator.h"
#include <utility>

class MIDStub {
public:
  static constexpr unsigned long long seed = 57;
  static LinearCongruentialGenerator lcg;
  MIDStub() = default;
  template<typename U>
  static double execute( U&& value ) {
    return lcg.exp( std::forward<U>( value ) );
  }

};

#endif
