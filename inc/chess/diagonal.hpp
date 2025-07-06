#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class diagonal : public std::ranges::view_interface<diagonal> {
public:
  using iterator = squares_iterator<9>;

  explicit operator bitboard() const;

  bitboard to_bitboard() const { return bitboard(*this); }
  
  iterator begin() const;
  
  iterator end() const;
  
  friend diagonal diagonal_of(square s);
  
private:
  explicit diagonal(square s);

  square sq_;
};

diagonal diagonal_of(square s);

} // namespace chess
