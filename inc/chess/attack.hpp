#pragma once

#include "bitboard.hpp"
#include "rotated_bitboard.hpp"
#include "player.hpp"

namespace chess {
  
bitboard rank_attack(square from, bitboard occupied);

bitboard file_attack(square from, rotated_bitboard_90 occupied);

bitboard diagonal_attack(square from, rotated_bitboard_45 occupied);

bitboard antidiagonal_attack(square from, rotated_bitboard_135 occupied);

bitboard pawns_attack(player turn, bitboard pawns, bitboard occupied);

bitboard knight_attack(square from);

inline bitboard rook_attack(square from, bitboard occupied, rotated_bitboard_90 occupied_90) {
  return rank_attack(from, occupied) | file_attack(from, occupied_90);
}

inline bitboard bishop_attack(square from, rotated_bitboard_45 occupied_45, rotated_bitboard_135 occupied_135) {
  return diagonal_attack(from, occupied_45) | antidiagonal_attack(from, occupied_135);
}

inline bitboard queen_attack(square from, bitboard occupied, rotated_bitboard_45 occupied_45, rotated_bitboard_90 occupied_90, rotated_bitboard_135 occupied_135) {
  return rook_attack(from, occupied, occupied_90) | bishop_attack(from, occupied_45, occupied_135);
}

bitboard king_attack(square from);

} // namespace chess
