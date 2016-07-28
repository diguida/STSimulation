#ifndef include_MIDStub_h
#define include_MIDStub_h

#include <memory>
#include <random>
#include <type_traits>

template < class UIntType,
                 UIntType a,
                 UIntType c,
                 UIntType m >
class MIDStub {
  typedef std::linear_congruential_engine< UIntType, a, c, m > engine_type;
public:
  explicit MIDStub( unsigned long long seed ):
    m_lce( new engine_type( seed ) ) {}
  template<typename U>
  auto execute( U&& lambda ) -> typename std::decay<decltype(lambda)>::type {
    // assuming the type of lambda is double:
    // * decltype(lambda) is double&
    // * std::decay<decltype(lambda)>::type is double;
    std::exponential_distribution<> d( std::forward<U>( lambda ) );
    return d( *m_lce );
  }
private:
  std::shared_ptr< engine_type > m_lce; 
};

#endif
