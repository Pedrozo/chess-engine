#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/direction.hpp"
#include "chess/rank_attack.hpp"
#include "chess/squares_sequence.hpp"
#include "chess/rotated_bitboard.hpp"

using std::size_t;

namespace chess {

rank_attack::rank_attack() {
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

      computed_[unsigned(s)][i] = attack;
    }
  }
}

bitboard rank_attack::operator()(square from, bitboard occupied) const {
  return computed_[unsigned(from)][static_cast<size_t>(align_rank(from, occupied))];
}

} // namespace chess
