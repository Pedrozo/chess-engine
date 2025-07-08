#include "chess/board/piece_centric.hpp"
#include "chess/attack.hpp"
#include "chess/utils.hpp"

namespace chess::board {

piece_centric::piece_centric(std::initializer_list<std::pair<square, player_piece>> pieces) {
  for (const auto& [s, pl_pi] : pieces) {
    const int pl = static_cast<int>(std::get<0>(pl_pi));
    const int pi = static_cast<int>(std::get<1>(pl_pi));
    const bitboard b(s);

    pieces_[pl][pi].set(s);
    player_occupied_[pl].set(s);

    occupied_.set(s);
    occupied_45_.set(s);
    occupied_90_.set(s);
    occupied_135_.set(s);
  }

  update_attack_boards();
}

bitboard piece_centric::positions() const {
  return occupied_;
}

rotated_bitboard_45 piece_centric::rotated_positions_45() const {
  return occupied_45_;
}

rotated_bitboard_90 piece_centric::rotated_positions_90() const {
  return occupied_90_;
}

rotated_bitboard_135 piece_centric::rotated_positions_135() const {
  return occupied_135_;
}

bitboard piece_centric::positions_of(player p) const {
  return player_occupied_[static_cast<int>(p)];
}

bitboard piece_centric::positions_of(player_piece pp) const {
  return pieces_[static_cast<int>(std::get<0>(pp))][static_cast<int>(std::get<1>(pp))];
}

bitboard piece_centric::attack_of(player p) const {
  return player_attacks_[static_cast<int>(p)];
}

void piece_centric::make_move(square from, square to, player_piece moved_piece, optional_player_piece captured_piece) {
  const int playing  = static_cast<int>(std::get<0>(moved_piece));
  const int opponent = !playing;
  const int moved    = static_cast<int>(std::get<1>(moved_piece));

  const bitboard from_bb(from);
  const bitboard to_bb(to);
  const bitboard from_to_bb = from_bb | to_bb;

  pieces_[playing][moved]   ^= from_to_bb;
  player_occupied_[playing] ^= from_to_bb;

  if (captured_piece) {
    const int captured = static_cast<int>(std::get<1>(captured_piece.value()));
    pieces_[opponent][captured] ^= to_bb;
    player_occupied_[opponent]  ^= to_bb;
  } else {
    occupied_.flip(to);
    occupied_45_.flip(to);
    occupied_90_.flip(to);
    occupied_135_.flip(to);
  }

  occupied_.flip(from);
  occupied_45_.flip(from);
  occupied_90_.flip(from);
  occupied_135_.flip(from);

  update_attack_boards();
}

bool piece_centric::in_check(player p) const {
  return bool(attack_of(opponent_player(p)) & positions_of(player_piece{p, piece::king}));
}

void piece_centric::update_attack_boards() {
  for (int i = 0; i < 2; i++) {
    const player playing = static_cast<player>(i);

    player_attacks_[i] = pawns_attack(playing, pieces_[i][static_cast<int>(piece::pawn)], occupied_);

    for (const bitboard bb : bitboard_squares(pieces_[i][static_cast<int>(piece::knight)])) {
      player_attacks_[i] |= knight_attack(square(bb));
    }

    for (const bitboard bb : bitboard_squares(pieces_[i][static_cast<int>(piece::rook)])) {
      player_attacks_[i] |= rook_attack(square(bb), occupied_, occupied_90_);
    }

    for (const bitboard bb : bitboard_squares(pieces_[i][static_cast<int>(piece::bishop)])) {
      player_attacks_[i] |= bishop_attack(square(bb), occupied_45_, occupied_135_);
    }

    for (const bitboard bb : bitboard_squares(pieces_[i][static_cast<int>(piece::queen)])) {
      player_attacks_[i] |= queen_attack(square(bb), occupied_, occupied_45_, occupied_90_, occupied_135_);
    }

    for (const bitboard bb : bitboard_squares(pieces_[i][static_cast<int>(piece::king)])) {
      player_attacks_[i] |= king_attack(square(bb));
    }
  }
}

} // namespace chess::board
