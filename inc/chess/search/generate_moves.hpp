#pragma once

#include <vector>

#include "chess/board/piece_centric.hpp"

namespace chess::search {

std::vector<std::pair<square, square>> generate_moves(const board::piece_centric& pieces_board, player turn);

} // namespace chess::search
