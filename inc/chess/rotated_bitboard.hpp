#pragma once

#include <tuple>
#include <functional>

#include "bitboard.hpp"

namespace chess {

void initialize_rotated_boards();

struct rotate_45_fn { square operator()(square s) const; };

struct rotate_90_fn { square operator()(square s) const; };

struct rotate_135_fn { square operator()(square s) const; };

inline constexpr rotate_45_fn rotate_45{};

inline constexpr rotate_90_fn rotate_90{};

inline constexpr rotate_135_fn rotate_135{};

template<typename R>
class rotated_bitboard {
public:
  explicit constexpr rotated_bitboard(R rotation = R()) : tup_(bitboard(0), rotation) {}

  constexpr void set(square s) { board().set(rotate(s)); }

  constexpr void reset(square s) { board().reset(rotate(s)); }

  constexpr void flip(square s) { board().flip(rotate(s)); }

  explicit constexpr operator bitboard() const { return board(); }

private:
  constexpr bitboard& board() { return std::get<0>(tup_); }

  constexpr const bitboard& board() const { return std::get<0>(tup_); }

  constexpr square rotate(square s) { return std::invoke(std::get<1>(tup_), s); }

  std::tuple<bitboard, R> tup_;
};

using rotated_bitboard_45 = rotated_bitboard<rotate_45_fn>;

using rotated_bitboard_90 = rotated_bitboard<rotate_90_fn>;

using rotated_bitboard_135 = rotated_bitboard<rotate_135_fn>;

std::byte align_rank(square s, bitboard bb);

std::byte align_file(square s, rotated_bitboard_90 bb);

std::byte align_diagonal(square s, rotated_bitboard_45 bb);

std::byte align_antidiagonal(square s, rotated_bitboard_135 bb);

} // namespace chess
