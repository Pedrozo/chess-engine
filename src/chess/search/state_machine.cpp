#include "chess/search/generate_moves.hpp"
#include "chess/search/state_machine.hpp"

namespace chess::search {

namespace  {

constexpr int piece_score(piece p) {
  switch (p) {
    case piece::pawn:
      return 1;
    
    case piece::knight:
    case piece::bishop:
      return 3;
    
    case piece::rook:
      return 5;

    case piece::queen:
      return 9;

    default:
      return 0;
  }
}

} // namespace 

state_machine::state_machine(std::initializer_list<std::pair<square, player_piece>> initial)
  : squares_(initial), pieces_(initial), score_(0) {

  for (auto [_, pp] : initial) {
    if (std::get<0>(pp) == player::white) {
      score_ += piece_score(std::get<1>(pp));
    } else {
      score_ += piece_score(std::get<1>(pp));
    }
  }
}

bool state_machine::game_over(player playing) const {
  return pieces_.in_check(opponent_player(playing));
}

int state_machine::eval() const {
  return score_;
}

std::vector<std::pair<square, square>> state_machine::childs(player playing) const {
  return generate_moves(pieces_, playing);
}

void state_machine::commit(const std::pair<square, square>& from_to) {
  const auto [from, to] = from_to;

  const player_piece moved = squares_[from].value();
  const optional_player_piece captured = squares_.make_move(from, to);

  pieces_.make_move(from, to, moved, captured);
  hist_.emplace(from, to, captured);

  if (captured) {
    const auto [playing, captured_piece] = captured.value();

    if (player::white == playing) {
      score_ -= piece_score(captured_piece);
    } else {
      score_ += piece_score(captured_piece);
    }
  }
}

void state_machine::revert() {
  const auto [from, to, captured] = hist_.top();

  squares_.unmake_move(from, to, captured);
  pieces_.make_move(from, to, squares_[from].value(), captured);

  if (captured) {
    const auto [playing, captured_piece] = captured.value();

    if (player::white == playing) {
      score_ += piece_score(captured_piece);
    } else {
      score_ -= piece_score(captured_piece);
    }
  }

  hist_.pop();
}

} // namespace chess::search
