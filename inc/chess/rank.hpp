#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class rank : public std::ranges::view_interface<rank> {
public:
  using iterator = squares_iterator<1>;

  explicit constexpr rank(unsigned idx) : idx_(idx) {
    if (idx > 7) {
      throw std::invalid_argument("rank index must be between 0-7");
    }
  }

  explicit constexpr operator bitboard() const {
    return bitboard(0xFF) << (idx_ << 3);
  }

  constexpr bitboard to_bitboard() const { return bitboard(*this); }

  constexpr iterator begin() const { return iterator(idx_ << 3); }

  constexpr iterator end() const { return iterator((idx_ + 1) << 3); }

private:
  unsigned idx_;
};

constexpr rank rank_of(square s) {
  return rank(unsigned(s) >> 3);
}

} // namespace chess
