#ifndef include_MIDStub_h
#define include_MIDStub_h

#include <random>
#include <type_traits>

/**
 * @brief A class simulating the execution of a module in statistical testing.
 *
 * The class instantiates a random number engine based on Linear
 * congruential generator (LCG).
 * The template parameter @p _UIntType must be an unsigned integral type
 * large enough to store values up to (m-1).
 * The template parameters @p __a (the multiplier) and @p __c (the increment)
 * must be less than @p __m (the modulus).
 * At every access, a random interfailure time with exponential distribution
 * is generated. The rate is passed as argument in the call.
 */

template < typename _UIntType, _UIntType __a, _UIntType __c, _UIntType __m >
class MIDStub {
  /** The type of the random number engine, as in the random library of the STL. */
  typedef std::linear_congruential_engine< _UIntType, __a, __c, __m > engine_type;
public:
  /** The type of the generated random value. */
  typedef _UIntType result_type;

  /** The multiplier. */
  static constexpr result_type multiplier   = __a;
  /** An increment. */
  static constexpr result_type increment    = __c;
  /** The modulus. */
  static constexpr result_type modulus      = __m;

  /**
   * @brief Constructs a %linear_congruential_engine random number
   *        generator engine with seed @p __seed.
   * The constructor initialises an instance of %std::linear_congruential_engine
   * with a seed provided as input.
   *
   * @param __seed The initial seed value.
   */
  explicit MIDStub( _UIntType __seed ):
    m_lce{ __seed } {}

  /**
   * @brief Generate an interfailure time following an exponential distribution
   *        with rate @p __lambda.
   *
   * @param __lambda The exponential rate: its type should be one of float, double, or long double.
   */
  template<typename U>
  auto execute( U&& __lambda ) -> typename std::decay<decltype(__lambda)>::type {
    // assuming the type of __lambda is double:
    // * decltype(__lambda), i.e. U, is double&
    // * std::decay<decltype(__lambda)>::type, i.e. std::decay<U>::type, is double.
    std::exponential_distribution<typename std::decay<U>::type> d( std::forward<U>( __lambda ) );
    return d( m_lce );
  }
private:
  /** The random number generator engine based on LCG. */
  engine_type m_lce; 
};

#endif
