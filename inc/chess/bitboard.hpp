#pragma once

#include <cstdint>
#include <ranges>
#include <iostream>
#include <bit>
#include "square.hpp"

namespace chess {

class bitboard {
public:
  constexpr bitboard() : board_() {}

  explicit constexpr bitboard(std::uint64_t board) : board_(board) {}

  explicit constexpr bitboard(square s) : board_(std::uint64_t(1) << unsigned(s)) {}

  explicit constexpr operator std::uint64_t() const { return board_; }

  explicit constexpr operator bool() const { return bool(board_); }

  explicit constexpr operator square() const { return square(std::countr_zero(board_)); }

  constexpr void set(square s) { *this |= bitboard(s); }

  constexpr void reset(square s) { *this &= ~bitboard(s); }

  constexpr void flip(square s) { *this ^= bitboard(s); }

  constexpr int popcount() const { return std::popcount(board_); }

  constexpr bitboard operator~() const { return bitboard(~board_); }

  constexpr bitboard operator<<(std::size_t pos) const { return bitboard(board_ << pos); }

  constexpr bitboard operator>>(std::size_t pos) const { return bitboard(board_ >> pos); }

  constexpr bitboard& operator<<=(std::size_t pos) { board_ <<= pos; return *this; }

  constexpr bitboard& operator>>=(std::size_t pos) { board_ >>= pos; return *this; }

  constexpr bitboard& operator&=(bitboard b) { board_ &= b.board_; return *this; }

  constexpr bitboard& operator|=(bitboard b) { board_ |= b.board_; return *this; }

  constexpr bitboard& operator^=(bitboard b) { board_ ^= b.board_; return *this; }

  friend constexpr bool operator==(bitboard lhs, bitboard rhs) {
    return lhs.board_ == rhs.board_;
  }

  friend constexpr bool operator!=(bitboard lhs, bitboard rhs) {
    return lhs.board_ != rhs.board_;
  }

  friend constexpr bitboard operator|(bitboard lhs, bitboard rhs) {
    return bitboard(lhs.board_ | rhs.board_);
  }

  friend constexpr bitboard operator&(bitboard lhs, bitboard rhs) {
    return bitboard(lhs.board_ & rhs.board_);
  }

  friend constexpr bitboard operator^(bitboard lhs, bitboard rhs) {
    return bitboard(lhs.board_ ^ rhs.board_);
  }

private:
  std::uint64_t board_;
};

std::ostream& operator<<(std::ostream& os, bitboard board);

} // namespace chess
