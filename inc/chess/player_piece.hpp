#pragma once

#include "player.hpp"
#include "piece.hpp"

#include <tuple>

namespace chess {

using player_piece = std::tuple<player, piece>;

} // namespace chess
