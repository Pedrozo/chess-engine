#pragma once

#include <algorithm>
#include <utility>

#include "chess/player.hpp"
#include "minimax.hpp"

namespace chess::search {

auto alphabeta(auto& state, unsigned depth, player playing) {
  return alphabeta(state, depth, -infinite_score, infinite_score, playing);
}

template<typename State, typename Move = game_move_t<State>>
auto alphabeta(State& state, unsigned depth, int alpha, int beta, player playing) -> std::pair<int, std::optional<Move>> {

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

      auto [score, _] = alphabeta(state, depth - 1, alpha, beta, player::black);
    
      state.revert();

      if (score > max_score) {
        max_score = score;
        best = child;
      }

      alpha = std::max(alpha, score);

      if (beta <= alpha) {
        break;
      }
    }

    return std::make_pair(max_score, best);
  } else {
    int min_score = infinite_score;
    std::optional<Move> best;

    for (const Move& child : state.childs(playing)) {
      state.commit(child);

      auto [score, _] = alphabeta(state, depth - 1, alpha, beta, player::white);
    
      state.revert();

      if (score < min_score) {
        min_score = score;
        best = child;
      }

      beta = std::min(beta, score);

      if (beta <= alpha) {
        break;
      }
    }

    return std::make_pair(min_score, best);
  }
}

} // namespace chess::search
