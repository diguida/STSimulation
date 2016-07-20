#include "../include/MIDTestDriver.h"

MIDTestDriver::MIDTestDriver( double tau ):
  m_tau( tau ) {}

double MIDTestDriver::callMID() const {
  return 0.;
}

void MIDTestDriver::setMeanTime( double tau ) {
  m_tau = tau;
}

double MIDTestDriver::getMeanTime() const {
  return m_tau;
}
