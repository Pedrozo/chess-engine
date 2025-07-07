#pragma once

#include <ranges>

#include "bitboard.hpp"
#include "squares_iterator.hpp"

namespace chess {

class file : public std::ranges::view_interface<file> {
public:
  using iterator = squares_iterator<8>;
  using reverse_iterator = std::reverse_iterator<iterator>;

  explicit constexpr file(unsigned idx) : idx_(idx) {
    if (idx > 7) {
      throw std::invalid_argument("file index must be between 0-7");
    }
  }

  explicit constexpr operator bitboard() const {
    return bitboard(0x101010101010101) << idx_;
  }

  constexpr bitboard to_bitboard() const { return bitboard(*this); }

  constexpr iterator begin() const { return iterator(idx_); }

  constexpr iterator end() const { return iterator(idx_ + 64); }

  constexpr reverse_iterator rbegin() const { return reverse_iterator(end()); }

  constexpr reverse_iterator rend() const { return reverse_iterator(begin()); }

private:
  unsigned idx_;
};

constexpr file file_of(square s) {
  return file(unsigned(s) & 0b111);
}

} // namespace chess
