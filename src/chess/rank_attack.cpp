#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/direction.hpp"
#include "chess/attack.hpp"
#include "chess/squares_sequence.hpp"
#include "chess/rotated_bitboard.hpp"

using std::size_t;
using std::uint64_t;

namespace chess {

namespace {

bitboard precomputed_attacks[64][256];

} // namespace

void detail::initialize_rank_attacks() {
  for (square s : all_squares()) {
    for (unsigned i = 0; i < 256; i++) {
      const bitboard occupied = bitboard(i) << unsigned(*rank_of(s).begin());
      bitboard attack(0);

      auto bit = bitboard(s);

      while (!(bit & bitboard(file(7)))) {
        bit = to_east(bit);
        attack |= bit;

        if (bit & occupied) {
          break;
        }
      }

      bit = bitboard(s);

      while (!(bit & bitboard(file(0)))) {
        bit = to_west(bit);
        attack |= bit;

        if (bit & occupied) {
          break;
        }
      }

      precomputed_attacks[unsigned(s)][i] = attack;
    }
  }
}

bitboard rank_attack(square from, bitboard occupied) {
  return precomputed_attacks[unsigned(from)][uint64_t(align_rank(from, occupied))];
}

} // namespace chess
