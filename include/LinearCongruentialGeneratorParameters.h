#ifndef include_LinearCongruentialGeneratorParameters_h
#define include_LinearCongruentialGeneratorParameters_h

/**
 * @brief A utility class containing the parameters
 * for the Linear Congruential Generator used in the simulation.
 */
class LinearCongruentialGeneratorParameters {
public:
  /** The type of the range of the distribution. */
  typedef unsigned long long result_type;

  /** The default constructor. */
  LinearCongruentialGeneratorParameters() {}

  /**
   * @brief The multiplier.
   *
   * The value of the multiplier guarantees maximum period
   * and allows to pass tests for randomness.
   */
  static constexpr result_type multiplier = 1220703125;

  /**
   * @brief The increment.
   *
   * The value of the increment is 0,
   * so the LCG will use the multiplicative method.
   */
  static constexpr result_type increment = 0;

  /**
   * @ brief The modulus.
   *
   * The value of the modulus is set to 2^31.
   */
  static constexpr result_type modulus = 1ULL << 31;
};

#endif
