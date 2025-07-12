#pragma once

#include <array>
#include <vector>

#include "chess/player_piece.hpp"
#include "chess/square.hpp"
#include "chess/bitboard.hpp"
#include "chess/rotated_bitboard.hpp"

namespace chess::board {

class piece_centric {
public:
  explicit piece_centric(std::initializer_list<std::pair<square, player_piece>> pieces);

  bitboard occupied() const;

  rotated_bitboard_45 rotated_occupied_45() const;

  rotated_bitboard_90 rotated_occupied_90() const;
  
  rotated_bitboard_135 rotated_occupied_135() const;

  bitboard occupied_of(player p) const;

  bitboard occupied_of(player_piece pp) const;

  bitboard attack_of(player p) const;

  bool in_check(player p) const;

  void make_move(square from, square to, player_piece moved_piece, optional_player_piece captured_piece);

private:
  void update_attack_boards();

  bitboard pieces_[2][6];
  bitboard player_occupied_[2];
  bitboard player_attacks_[2];
  bitboard occupied_;
  rotated_bitboard_45 occupied_45_;
  rotated_bitboard_90 occupied_90_;
  rotated_bitboard_135 occupied_135_;
};

} // namespace chess::board
