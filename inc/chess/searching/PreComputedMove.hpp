#ifndef CHESS_SEARCHING_PRECOMPUTEDMOVE_HPP
#define CHESS_SEARCHING_PRECOMPUTEDMOVE_HPP

#include "chess/Player.hpp"
#include "chess/Square.hpp"
#include "chess/BitBoard.hpp"
#include "chess/searching/PositionBitBoards.hpp"
#include "chess/searching/Position.hpp"

namespace chess::searching {

class Position;

struct PreComputedMove {
    PreComputedMove(Square from, Square to)
        : from(from), to(to), positionBitBoards() {}

    PreComputedMove(Square from, Square to, PositionBitBoards positionBitBoards)
        : from(from), to(to), positionBitBoards(positionBitBoards) {}

    Square from;
    Square to;
    PositionBitBoards positionBitBoards;
};

PreComputedMove makePreComputedMove(Square from, Square to, const Position& position);

} // namespace chess::searching

#endif // CHESS_SEARCHING_PRECOMPUTEDMOVE_HPP
