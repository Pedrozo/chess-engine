#pragma once

#include "chess/bitboard.hpp"

namespace chess {

class rank_attack {
public:
  rank_attack();

  bitboard operator()(square from, bitboard occupied) const;

private:
  bitboard computed_[64][256];
};

} // namespace chess
