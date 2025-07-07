#include "chess/initialization.hpp"
#include "chess/attack.hpp"
#include "chess/squares_sequence.hpp"
#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/direction.hpp"

namespace chess {

namespace {

bitboard precomputed_attacks[64];

} // namespace

void initialize_king_attacks() {
  constexpr bitboard not_bottom = ~bitboard(rank(0));
  constexpr bitboard not_top    = ~bitboard(rank(7));
  constexpr bitboard not_left   = ~bitboard(file(0));
  constexpr bitboard not_right  = ~bitboard(file(7));

  for (const square from : all_squares()) {
    const bitboard from_bit(from);
    bitboard attack;

    if (from_bit & not_bottom) {
      attack.set(to_south(from));
    }
  
    if (from_bit & not_top) {
      attack.set(to_north(from));
    }

    if (from_bit & not_left) {
      attack.set(to_west(from));
    }

    if (from_bit & not_right) {
      attack.set(to_east(from));
    }

    if (from_bit & not_bottom & not_left) {
      attack.set(to_southwest(from));
    }

    if (from_bit & not_bottom & not_right) {
      attack.set(to_southeast(from));
    }

    if (from_bit & not_top & not_left) {
      attack.set(to_northwest(from));
    }

    if (from_bit & not_top & not_right) {
      attack.set(to_northeast(from));
    }

    precomputed_attacks[unsigned(from)] = attack;
  }
}

bitboard king_attack(square from) {
  return precomputed_attacks[unsigned(from)];
}

} // namespace chess
