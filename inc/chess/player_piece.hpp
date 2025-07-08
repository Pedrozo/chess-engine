#pragma once

#include "player.hpp"
#include "piece.hpp"

#include <tuple>
#include <optional>

namespace chess {

using player_piece = std::tuple<player, piece>;

using optional_player_piece = std::optional<player_piece>;

inline constexpr player_piece white_king{player::white, piece::king};

inline constexpr player_piece white_queen{player::white, piece::queen};

inline constexpr player_piece white_bishop{player::white, piece::bishop};

inline constexpr player_piece white_knight{player::white, piece::knight};

inline constexpr player_piece white_rook{player::white, piece::rook};

inline constexpr player_piece white_pawn{player::white, piece::pawn};

inline constexpr player_piece black_king{player::black, piece::king};

inline constexpr player_piece black_queen{player::black, piece::queen};

inline constexpr player_piece black_bishop{player::black, piece::bishop};

inline constexpr player_piece black_knight{player::black, piece::knight};

inline constexpr player_piece black_rook{player::black, piece::rook};

inline constexpr player_piece black_pawn{player::black, piece::pawn};

} // namespace chess
