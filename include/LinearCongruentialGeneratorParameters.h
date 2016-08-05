#ifndef include_LinearCongruentialGeneratorParameters_h
#define include_LinearCongruentialGeneratorParameters_h

class LinearCongruentialGeneratorParameters {
public:
  typedef unsigned long long result_type;
  LinearCongruentialGeneratorParameters() {}
  // the value of the multiplier guarantees maximum period
  // and allows to pass tests for randomness.
  static constexpr result_type multiplier = 1220703125;
  // increment set to 0, so multiplicative method
  static constexpr result_type increment = 0;
  //the modulus is set to 2^31
  static constexpr result_type modulus = 1ULL << 31;
};

#endif
