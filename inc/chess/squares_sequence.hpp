#pragma once

#include "square.hpp"
#include "squares_iterator.hpp"

namespace chess {

template<int I>
class squares_sequence {
public:
  using iterator = squares_iterator<I>;

  constexpr squares_sequence(int begin, int end) : begin_(begin), end_(end) {}

  constexpr iterator begin() const { return begin_; }

  constexpr iterator end() const { return end_; }

private:
  iterator begin_;
  iterator end_;
};

constexpr auto all_squares() { return squares_sequence<1>(0, 64); }

} // namespace chess
