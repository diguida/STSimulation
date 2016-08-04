#ifndef include_MIDTestDriver_h
#define include_MIDTestDriver_h

#include "MIDStub.h"

#include <memory>

/**
 * @brief A class controlling and calling the module
 * whose statistical testing phase is simulated.
 * 
 * The class is constructed from a shared pointer to an instance of
 * the template class MIDStub, which is retained as a data member.
 * In this way, it enforces the sharing of the same random number sequence
 * by all the instances of the driver constructed from the same pointer.
 */

template < typename _Stub, typename _RealType = double >
class MIDTestDriver {
public:
  /** The type of the range of the distribution. */
  typedef _RealType result_type;

  /**
   * @brief Constructs a test driver able to yield an exponential distribution
   *        with inverse scale parameter @f$\lambda@f$ from a random number generator engine.
   *
   * @param __midstub A shared pointer to a MIDStub template class, yielding random numbers
   *        based on Linear Congruential Generator according to an exponential distribution
   *        with rate @p __lambda, representing the interfailure times of the module
   *        whose statistical testing phase is simulated.
   * @param __lambda The exponential rate used to yield the exponential distribution:
   *        its type should be one of float, double, or long double. Defaults to 1.
   */
  explicit MIDTestDriver( std::shared_ptr<_Stub> __midstub, result_type const & __lambda = result_type(1) ):
    m_midstub( __midstub )
  , m_lambda( __lambda ) {}

  /**
   * @brief Simulation of the module running till a failure happens.
   *        
   * @return An interfailure time produced by an exponential distribution
   *         with inverse scale parameter @p m_lambda
   *         from a random number generator engine defined in @p m_midstub.
   */
  result_type callMID() const {
    return m_midstub->execute( m_lambda );
  }

  /**
   * @brief Sets the rate of the distribution.
   * @param __lambda The new rate of the distribution.
   */
  void lambda( result_type const & __lambda ) {
    m_lambda = __lambda;
  }

  /**
   * @brief Returns the inverse scale parameter of the distribution.
   */
  result_type lambda() const {
    return m_lambda;
  }

private:
  std::shared_ptr<_Stub> m_midstub;
  result_type m_lambda;
};

#endif
