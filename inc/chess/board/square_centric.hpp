#pragma once

#include <array>
#include <stack>
#include <optional>

#include "chess/square.hpp"
#include "chess/player_piece.hpp"

namespace chess::board {

class square_centric {
public:
  explicit square_centric(std::initializer_list<std::pair<square, player_piece>> pieces);

  optional_player_piece operator[](square s) const;

  optional_player_piece make_move(square from, square to);

  void unmake_move(square from, square to, optional_player_piece captured);

private:
  std::array<optional_player_piece, 64> board_;
};

} // namespace chess::board
