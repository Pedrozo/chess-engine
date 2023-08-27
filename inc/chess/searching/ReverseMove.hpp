#ifndef CHESS_SEARCHING_REVERSEMOVE_HPP
#define CHESS_SEARCHING_REVERSEMOVE_HPP

#include "chess/Square.hpp"
#include "chess/BitBoard.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/searching/PositionBitBoards.hpp"

#include <optional>

namespace chess::searching {

struct ReverseMove {
    ReverseMove(Square from, Square to)
        : from(from), to(to), previousBitBoards(), captured() {}

    Square from;
    Square to;
    PositionBitBoards previousBitBoards;
    std::optional<PlayerPiece> captured;
};

} // namespace chess::searching

#endif // CHESS_SEARCHING_REVERSEMOVE_HPP
