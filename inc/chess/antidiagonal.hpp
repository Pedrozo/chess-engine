#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class antidiagonal : public std::ranges::view_interface<antidiagonal> {
public:
  using iterator = squares_iterator<7>;

  explicit operator bitboard() const;

  bitboard to_bitboard() const { return bitboard(*this); }
  
  iterator begin() const;
  
  iterator end() const;
  
  friend antidiagonal antidiagonal_of(square s);
  
private:
  explicit antidiagonal(square s);

  square sq_;
};

antidiagonal antidiagonal_of(square s);

} // namespace chess
