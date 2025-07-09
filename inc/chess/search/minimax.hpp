#pragma once

#include <algorithm>
#include <utility>

#include "chess/player.hpp"

namespace chess::search {

inline constexpr int infinite_score = 666;

template<typename T>
using game_move_t = std::iter_value_t<decltype(std::declval<const T&>().childs(std::declval<chess::player>()))>;

template<typename State, typename Move = game_move_t<State>>
auto minimax(State& state, unsigned depth, player playing) -> std::pair<int, std::optional<Move>> {

  if (state.game_over(playing)) {
    return std::make_pair(
      (playing == player::white) ? infinite_score : -infinite_score, std::optional<Move>());
  }

  if (depth == 0) {
    return std::make_pair(state.eval(), std::optional<Move>());
  }

  if (playing == player::white) {
    int max_score = -infinite_score;
    std::optional<Move> best;

    for (const Move& child : state.childs(playing)) {
      state.commit(child);

      auto [score, _] = minimax(state, depth - 1, player::black);
    
      state.revert();

      if (score > max_score) {
        max_score = score;
        best = child;
      }
    }

    return std::make_pair(max_score, best);
  } else {
    int min_score = infinite_score;
    std::optional<Move> best;

    for (const Move& child : state.childs(playing)) {
      state.commit(child);

      auto [score, _] = minimax(state, depth - 1, player::white);
    
      state.revert();

      if (score < min_score) {
        min_score = score;
        best = child;
      }
    }

    return std::make_pair(min_score, best);
  }
}

} // namespace chess::search
