#ifndef include_MIDTestDriver_h
#define include_MIDTestDriver_h

class MIDTestDriver {
public:
  explicit MIDTestDriver( double tau );
  double callMID() const;
  void setMeanTime( double tau );
  double getMeanTime() const;
private:
  double m_tau;
};

#endif
