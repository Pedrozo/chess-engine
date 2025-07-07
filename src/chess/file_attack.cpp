#include <ranges>

#include "chess/direction.hpp"
#include "chess/file.hpp"
#include "chess/attack.hpp"
#include "chess/squares_sequence.hpp"

namespace ranges = std::ranges;
namespace views = std::views;

using std::size_t;
using std::uint64_t;

namespace chess {

namespace {

bitboard precomputed_attacks[64][256];

} // namespace

void detail::initialize_file_attacks() {
  for (square from : all_squares()) {
    for (unsigned i = 0; i < 256; i++) {
      const bitboard occupied{uint64_t(i)};
      bitboard attack;
      rotated_bitboard_90 rotated_attack;

      const file file_squares = file_of(from);
      const auto squares_iter = std::find(file_squares.begin(), file_squares.end(), from);

      for (const square s : ranges::subrange(std::next(squares_iter), file_squares.end())) {
        attack.set(s);
        rotated_attack.set(s);

        if (occupied & align_file(from, rotated_attack)) {
          break;
        }
      }

      rotated_attack = rotated_bitboard_90{};

      for (const square s : ranges::subrange(std::reverse_iterator(squares_iter), file_squares.rend())) {
        attack.set(s);
        rotated_attack.set(s);

        if (occupied & align_file(from, rotated_attack)) {
          break;
        }
      }

      precomputed_attacks[unsigned(from)][i] = attack;
    }
  }
}

bitboard file_attack(square from, rotated_bitboard_90 occupied) {
  return precomputed_attacks[unsigned(from)][uint64_t(align_file(from, occupied))];
}

} // namespace chess
