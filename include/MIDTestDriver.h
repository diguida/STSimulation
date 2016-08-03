#ifndef include_MIDTestDriver_h
#define include_MIDTestDriver_h

#include <memory>
#include "MIDStub.h"

template < class Stub >
class MIDTestDriver {
public:
  explicit MIDTestDriver( std::shared_ptr<Stub> midstub ):
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
  std::shared_ptr<Stub> p_midstub;
  double m_lambda;
};

#endif
