#include "chess/attack.hpp"
#include "chess/squares_sequence.hpp"
#include "chess/diagonal.hpp"
#include "chess/initialization.hpp"

#include <ranges>

using std::size_t;
using std::uint64_t;

namespace ranges = std::ranges;
namespace views = std::views;

namespace chess {

namespace {

bitboard precomputed_attacks[64][256];

} // namespace

void initialize_diagonal_attacks() {
  for (const square from : all_squares()) {
    for (unsigned i = 0; i < 256; i++) {
      const bitboard occupied{uint64_t(i)};
      bitboard attack;
      
      const diagonal sequence = diagonal_of(from);
      const auto iter = std::find(sequence.begin(), sequence.end(), from);
      
      auto left_side = ranges::subrange(std::reverse_iterator(iter), sequence.rend());
      auto right_side = ranges::subrange(std::next(iter), sequence.end());
      
      for (const square s : right_side) {
        attack.set(s);

        rotated_bitboard_45 rotated_attack;
        rotated_attack.set(s);

        if (occupied & align_diagonal(from, rotated_attack)) {
          break;
        }
      }

      for (const square s : left_side) {
        attack.set(s);

        rotated_bitboard_45 rotated_attack;
        rotated_attack.set(s);

        if (occupied & align_diagonal(from, rotated_attack)) {
          break;
        }
      }

      precomputed_attacks[unsigned(from)][i] = attack;
    }
  }
}

bitboard diagonal_attack(square from, rotated_bitboard_45 occupied) {
  return precomputed_attacks[unsigned(from)][uint64_t(align_diagonal(from, occupied))];
}

} // namespace chess
