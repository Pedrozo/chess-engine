#pragma once

#include "square.hpp"
#include "bitboard.hpp"

namespace chess {

template<int N>
struct to_direction_fn {
  static constexpr int step() { return N; }

  constexpr square operator()(square s, int count = 1) const {
    return square(unsigned(s) + count * N);
  }

  constexpr bitboard operator()(bitboard b, int count = 1) const {
    if constexpr (N > 0) {
      return b << (N * count);
    } else {
      return b >> (-N * count);
    }
  }
};

inline constexpr auto to_north = to_direction_fn<8>{};

inline constexpr auto to_south = to_direction_fn<-8>{};

inline constexpr auto to_east = to_direction_fn<1>{};

inline constexpr auto to_west = to_direction_fn<-1>{};

} // namespace chess
