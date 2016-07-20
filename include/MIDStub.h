#ifndef include_MIDStub_h
#define include_MIDStub_h

#include "LinearCongruentialGenerator.h"
#include <utility>

class MIDStub {
public:
  explicit MIDStub( unsigned long long seed );
  template<typename U>
  double execute( U&& value ) {
    return m_lcg.exp( std::forward<U>( value ) );
  }
private:
  LinearCongruentialGenerator m_lcg;
};

#endif
