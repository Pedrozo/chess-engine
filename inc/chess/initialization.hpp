#pragma once

namespace chess {

void initialize_rotated_boards();

void initialize_rank_attacks();

void initialize_file_attacks();

void initialize_diagonal_attacks();

void initialize_antidiagonal_attacks();

void initialize_knight_attacks();

void initialize_king_attacks();

inline void initialize() {
  initialize_rotated_boards();
  initialize_rank_attacks();
  initialize_file_attacks();
  initialize_diagonal_attacks();
  initialize_antidiagonal_attacks();
  initialize_knight_attacks();
  initialize_king_attacks();
}

} // namespace chess
