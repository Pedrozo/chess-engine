#include "chess/attack.hpp"
#include "chess/direction.hpp"
#include "chess/file.hpp"

namespace chess {

bitboard pawns_attack(player turn, bitboard pawns, bitboard occupied) {
  const auto to_forward = [turn] (auto s) {
    return turn == player::white ? to_north(s) : to_south(s);
  };

  bitboard attack;
  attack |=  to_forward(to_west(pawns & ~bitboard(file(0))));
  attack |=  to_forward(to_east(pawns & ~bitboard(file(7))));
  return attack & occupied;
}

} // namespace chess
