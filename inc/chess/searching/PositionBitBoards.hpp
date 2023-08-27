#ifndef CHESS_SEARCHING_POSITIONBITBOARDS_HPP
#define CHESS_SEARCHING_POSITIONBITBOARDS_HPP

#include "chess/OccupiedBitBoard.hpp"
#include "chess/searching/PlayerBitBoards.hpp"

namespace chess::searching {

struct PositionBitBoards {
    OccupiedBitBoard occupied;
    PlayerBitBoards players[2];

    friend bool operator==(const PositionBitBoards& a, const PositionBitBoards& b) {
        if (a.occupied != b.occupied)
            return false;

        return a.players[0] == b.players[0] && a.players[1] == b.players[1];
    }
};

} // namespace chess::searching


#endif // CHESS_SEARCHING_POSITIONBITBOARDS_HPP