#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class diagonal : public std::ranges::view_interface<diagonal> {
public:
  using iterator = squares_iterator<9>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  explicit operator bitboard() const;

  bitboard to_bitboard() const { return bitboard(*this); }
  
  iterator begin() const;
  
  iterator end() const;

  reverse_iterator rbegin() const { return reverse_iterator(end()); }

  reverse_iterator rend() const { return reverse_iterator(begin()); }
  
  friend diagonal diagonal_of(square s);
  
private:
  explicit diagonal(square s);

  square sq_;
};

diagonal diagonal_of(square s);

} // namespace chess
