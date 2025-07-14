#include "chess/board/piece_centric.hpp"
#include "chess/attack.hpp"
#include "chess/utils.hpp"

namespace chess::board {

namespace {

template<typename T>
concept xorable = requires (T& a, T& b) {
  { a ^ b } -> std::convertible_to<T>;
};

constexpr void move_pieces(square from, square to, auto&... boards) {
  bitboard const from_to_bb = bitboard(from) | bitboard(to);

  auto fn = [&] (auto self, auto& first, auto&... others) {
    if constexpr (xorable<decltype(first)>) {
      first ^= from_to_bb;
    } else {
      first.flip(from);
      first.flip(to);
    }

    if constexpr (sizeof...(others) > 0) {
      self(self, others...);
    }
  };

  fn(fn, boards...);
}

constexpr void remove_pieces(square from, auto&... boards) {
  bitboard const from_bb(from);

  auto fn = [&] (auto self, auto& first, auto&... others) {
    if constexpr (xorable<decltype(first)>) {
      first ^= from_bb;
    } else {
      first.flip(from);
    }

    if constexpr (sizeof...(others) > 0) {
      self(self, others...);
    }
  };

  fn(fn, boards...);
}

} // namespace


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

bitboard piece_centric::occupied() const {
  return occupied_;
}

rotated_bitboard_45 piece_centric::rotated_occupied_45() const {
  return occupied_45_;
}

rotated_bitboard_90 piece_centric::rotated_occupied_90() const {
  return occupied_90_;
}

rotated_bitboard_135 piece_centric::rotated_occupied_135() const {
  return occupied_135_;
}

bitboard piece_centric::occupied_of(player p) const {
  return player_occupied_[static_cast<int>(p)];
}

bitboard piece_centric::occupied_of(player_piece pp) const {
  return pieces_[static_cast<int>(std::get<0>(pp))][static_cast<int>(std::get<1>(pp))];
}

bitboard piece_centric::attacked_of(player p) const {
  return player_attacks_[static_cast<int>(p)];
}

void piece_centric::make_move(square from, square to, player_piece moved_piece) {
  const int playing = static_cast<int>(std::get<0>(moved_piece));
  const int moving = static_cast<int>(std::get<1>(moved_piece));

  move_pieces(from, to,
    pieces_[playing][moving], player_occupied_[playing], occupied_, occupied_45_, occupied_90_, occupied_135_);
  
  update_attack_boards();
}

void piece_centric::make_move(square from, square to, player_piece moved_piece, piece captured_piece) {
  const int playing = static_cast<int>(std::get<0>(moved_piece));
  const int moving = static_cast<int>(std::get<1>(moved_piece));
  const int capturing = static_cast<int>(captured_piece);
  const int opponent = !playing;

  move_pieces(from, to, pieces_[playing][moving], player_occupied_[playing]);
  remove_pieces(to, pieces_[opponent][capturing], player_occupied_[opponent]);
  remove_pieces(from, occupied_, occupied_45_, occupied_90_, occupied_135_);

  update_attack_boards();
}

bool piece_centric::in_check(player p) const {
  return bool(attacked_of(opponent_player(p)) & occupied_of(player_piece{p, piece::king}));
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
