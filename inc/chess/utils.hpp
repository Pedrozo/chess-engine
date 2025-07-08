#pragma once

#include "bitboard_squares_iterator.hpp"

#include <ranges>

namespace chess {

constexpr auto bitboard_squares(bitboard bb) {
  using iterator = bitboard_squares_iterator;
  return std::ranges::subrange(iterator(bb), iterator(bitboard(0)));
}

} // namespace chess
