#ifndef include_MIDTestDriver_h
#define include_MIDTestDriver_h

#include <memory>
#include <vector>
#include "MIDStub.h"

template < class UIntType,
                 UIntType a,
                 UIntType c,
                 UIntType m >
class MIDTestDriver {
  typedef MIDStub< UIntType, a, c, m > stub_type;

public:
  explicit MIDTestDriver( std::shared_ptr<stub_type> midstub ):
    p_midstub( midstub )
  , m_lambda( 0. ) {}

  double callMID() const {
    return p_midstub->execute( m_lambda );
  }

  void setRate( double lambda ) {
    m_lambda = lambda;
  }

  double getRate() const {
    return m_lambda;
  }

private:
  std::shared_ptr<stub_type> p_midstub;
  double m_lambda;
};

#endif
