#pragma once

#include "bitboard.hpp"

namespace chess {

class bitboard_squares_iterator {
public:
  using value_type = bitboard;
  using difference_type = std::ptrdiff_t;

  constexpr bitboard_squares_iterator() : bb_() {}

  explicit constexpr bitboard_squares_iterator(bitboard bb) : bb_(bb) {}

  constexpr bitboard operator*() const {
    return bb_ ^ (bb_ & bitboard(std::uint64_t(bb_) - 1));
  }

  constexpr bitboard_squares_iterator& operator++() {
    bb_ &= bitboard(std::uint64_t(bb_) - 1);
    return *this;
  }

  constexpr bitboard_squares_iterator operator++(int) {
    bitboard_squares_iterator prev = *this;
    ++(*this);
    prev.bb_ ^= bb_;
    return prev;
  }

  friend constexpr bool operator==(bitboard_squares_iterator lhs, bitboard_squares_iterator rhs) {
    return lhs.bb_ == rhs.bb_;
  }

  friend constexpr bool operator!=(bitboard_squares_iterator lhs, bitboard_squares_iterator rhs) {
    return lhs.bb_ != rhs.bb_;
  }

private:
  bitboard bb_;
};

} // namespace chess
