#ifndef include_LinearCongruentialGeneratorParameters_h
#define include_LinearCongruentialGeneratorParameters_h

class LinearCongruentialGeneratorParameters {
public:
  LinearCongruentialGeneratorParameters() {}
  //the modulus is set to 2^31
  static constexpr unsigned long long m = 1ULL << 31;
  // the value of the multiplier guarantees maximum period
  // and allows to pass tests for randomness.
  static constexpr unsigned long long a = 1220703125;
  // increment set to 0, so multiplicative method
  static constexpr unsigned long long c = 0;
};

#endif
