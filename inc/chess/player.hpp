#pragma once

namespace chess {

enum class player {
  white,
  black
};

constexpr player opponent_player(player p) {
  return p == player::white ? player::black : player::white;
}

} // namespace chess
