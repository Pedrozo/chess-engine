#pragma once

#include <stack>

#include "chess/player_piece.hpp"
#include "chess/board/piece_centric.hpp"
#include "chess/board/square_centric.hpp"

namespace chess::search {

class state_machine {
public:
  explicit state_machine(std::initializer_list<std::pair<square, player_piece>> initial);

  bool game_over(player playing) const;

  int eval() const;

  std::vector<std::pair<square, square>> childs(player playing) const;

  void commit(const std::pair<square, square>& from_to);

  void revert();

private:
  board::square_centric squares_;
  board::piece_centric pieces_;
  std::stack<std::tuple<square, square, optional_player_piece>> hist_;
  int score_;
};

} // namespace chess::search
