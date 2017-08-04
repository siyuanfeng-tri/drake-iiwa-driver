#pragma once

#include <stdexcept>

template <typename T> class DiscreteTimeLowPassFilter {
public:
  DiscreteTimeLowPassFilter(T cutoff_hz, T dt) {
    // https://en.wikipedia.org/wiki/Low-pass_filter
    T rc = 1 / (2 * M_PI * cutoff_hz);
    // sfeng's alpha is 1 - wiki's alpha.
    alpha_ = 1 - dt / (dt + rc);
    check_alpha();
  }

  // val_ = alpha_ * val_ + (1. - alpha_) * in
  DiscreteTimeLowPassFilter(T alpha) : alpha_(alpha) { check_alpha(); }

  void set_initial(T v = 0.) { val_ = v; }

  T filter(T in) {
    val_ = alpha_ * val_ + (1. - alpha_) * in;
    return val_;
  }

  T get_filtered() const { return val_; }

private:
  void check_alpha() {
    if (alpha_ > 1 || alpha_ < 0)
      throw std::logic_error("invalid alpha" + std::to_string(alpha_));
  }

  T val_{0};
  T alpha_{0};
};
