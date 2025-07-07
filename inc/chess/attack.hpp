#pragma once

#include "bitboard.hpp"
#include "rotated_bitboard.hpp"
#include "player.hpp"

namespace chess {
  
bitboard rank_attack(square from, bitboard occupied);

bitboard file_attack(square from, rotated_bitboard_90 occupied);

bitboard diagonal_attack(square from, rotated_bitboard_45 occupied);

bitboard antidiagonal_attack(square from, rotated_bitboard_135 occupied);

bitboard knight_attack(square from);

bitboard king_attack(square from);

bitboard pawns_attack(player turn, bitboard pawns);

} // namespace chess
