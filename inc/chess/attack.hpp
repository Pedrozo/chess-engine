#pragma once

#include "bitboard.hpp"
#include "rotated_bitboard.hpp"

namespace chess {
  
bitboard rank_attack(square from, bitboard occupied);

bitboard file_attack(square from, rotated_bitboard_90 occupied);

bitboard diagonal_attack(square from, rotated_bitboard_45 occupied);

bitboard antidiagonal_attack(square from, rotated_bitboard_135 occupied);

namespace detail {

void initialize_rank_attacks();

void initialize_file_attacks();

void initialize_diagonal_attacks();

void initialize_antidiagonal_attacks();

} // namespace detail

inline void initialize_attack_boards() {
  detail::initialize_rank_attacks();
  detail::initialize_file_attacks();
  detail::initialize_diagonal_attacks();
  // detail::initialize_antidiagonal_attacks();
}

} // namespace chess
