#include "chess/attack.hpp"
#include "chess/squares_sequence.hpp"
#include "chess/antidiagonal.hpp"

#include <ranges>

using std::size_t;
using std::uint64_t;

namespace ranges = std::ranges;
namespace views = std::views;

namespace chess {

namespace {

bitboard precomputed_attacks[64][256];

} // namespace

void detail::initialize_antidiagonal_attacks() {
  for (const square from : all_squares()) {
    for (unsigned i = 0; i < 256; i++) {
      const bitboard occupied{uint64_t(i)};
      bitboard attack;
      
      const antidiagonal sequence = antidiagonal_of(from);
      const auto iter = std::find(sequence.begin(), sequence.end(), from);
      
      auto left_side = ranges::subrange(std::reverse_iterator(iter), sequence.rend());
      auto right_side = ranges::subrange(std::next(iter), sequence.end());
      
      for (const square s : right_side) {
        attack.set(s);

        rotated_bitboard_135 rotated_attack;
        rotated_attack.set(s);

        if (occupied & align_antidiagonal(from, rotated_attack)) {
          break;
        }
      }

      for (const square s : left_side) {
        attack.set(s);

        rotated_bitboard_135 rotated_attack;
        rotated_attack.set(s);

        if (occupied & align_antidiagonal(from, rotated_attack)) {
          break;
        }
      }

      precomputed_attacks[unsigned(from)][i] = attack;
    }
  }
}

bitboard antidiagonal_attack(square from, rotated_bitboard_135 occupied) {
  return precomputed_attacks[unsigned(from)][uint64_t(align_antidiagonal(from, occupied))];
}

} // namespace chess
