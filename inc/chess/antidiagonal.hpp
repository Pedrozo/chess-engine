#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class antidiagonal : public std::ranges::view_interface<antidiagonal> {
public:
  using iterator = squares_iterator<7>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  explicit operator bitboard() const;

  bitboard to_bitboard() const { return bitboard(*this); }
  
  iterator begin() const;
  
  iterator end() const;

  reverse_iterator rbegin() const { return reverse_iterator(end()); }

  reverse_iterator rend() const { return reverse_iterator(begin()); }
  
  friend antidiagonal antidiagonal_of(square s);
  
private:
  explicit antidiagonal(square s);

  square sq_;
};

antidiagonal antidiagonal_of(square s);

} // namespace chess
