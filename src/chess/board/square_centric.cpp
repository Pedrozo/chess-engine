#include "chess/board/square_centric.hpp"

namespace chess::board {

square_centric::square_centric(std::initializer_list<std::pair<square, player_piece>> pieces) {
  for (const auto& [s, pp] : pieces) {
    board_[unsigned(s)] = pp;
  }
}

optional_player_piece square_centric::operator[](square s) const {
  return board_[unsigned(s)];
}

optional_player_piece square_centric::make_move(square from, square to) {
  const auto captured_piece = board_[unsigned(to)];
  board_[unsigned(to)] = board_[unsigned(from)];
  board_[unsigned(from)] = std::nullopt;
  return captured_piece;
}

void square_centric::unmake_move(square from, square to, optional_player_piece captured) {
  board_[unsigned(from)] = board_[unsigned(to)];
  board_[unsigned(to)] = captured;
}

} // namespace chess::board
