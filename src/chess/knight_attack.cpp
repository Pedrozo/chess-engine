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

void initialize_knight_attacks() {
  constexpr bitboard not_bottom = ~bitboard(rank(0));
  constexpr bitboard not_top =    ~bitboard(rank(7));
  constexpr bitboard not_left =   ~bitboard(file(0));
  constexpr bitboard not_right =  ~bitboard(file(7));

  constexpr bitboard not_double_bottom = not_bottom & ~bitboard(rank(1));
  constexpr bitboard not_double_top =    not_top    & ~bitboard(rank(6));
  constexpr bitboard not_double_left =   not_left   & ~bitboard(file(1));
  constexpr bitboard not_double_right =  not_right  & ~bitboard(file(6));


  for (const square from : all_squares()) {
    const bitboard from_bit(from);
    bitboard attack;

    if (from_bit & not_double_top & not_left) {
      attack.set(to_north(to_west(from), 2));
    }

    if (from_bit & not_double_top & not_right) {
      attack.set(to_north(to_east(from), 2));
    }

    if (from_bit & not_double_bottom & not_left) {
      attack.set(to_south(to_west(from), 2));
    }

    if (from_bit & not_double_bottom & not_right) {
      attack.set(to_south(to_east(from), 2));
    }

    if (from_bit & not_double_left & not_top) {
      attack.set(to_west(to_north(from), 2));
    }

    if (from_bit & not_double_left & not_bottom) {
      attack.set(to_west(to_south(from), 2));
    }

    if (from_bit & not_double_right & not_top) {
      attack.set(to_east(to_north(from), 2));
    }

    if (from_bit & not_double_right & not_bottom) {
      attack.set(to_east(to_south(from), 2));
    }

    precomputed_attacks[unsigned(from)] = attack;
  }
}

bitboard knight_attack(square from) {
  return precomputed_attacks[unsigned(from)];
}

} // namespace chess
