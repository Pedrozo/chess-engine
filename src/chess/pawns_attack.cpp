#include "chess/attack.hpp"
#include "chess/direction.hpp"
#include "chess/rank.hpp"
#include "chess/file.hpp"

namespace chess {

bitboard pawns_attack(player turn, bitboard pawns, bitboard occupied) {
  const auto to_forward = [turn] (auto s, std::size_t count = 1) {
    return turn == player::white ? to_north(s, count) : to_south(s, count);
  };

  const bitboard spawn((turn == player::white) ? rank(1) : rank(6));

  bitboard attack;

  attack |= to_forward(to_forward(pawns & spawn) & ~occupied) & ~occupied;
  attack |= to_forward(pawns) & ~occupied;

  attack |=  to_forward(to_west(pawns & ~bitboard(file(0)))) & occupied;
  attack |=  to_forward(to_east(pawns & ~bitboard(file(7)))) & occupied;

  return attack;
}

} // namespace chess
