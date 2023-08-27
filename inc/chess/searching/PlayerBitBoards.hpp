#ifndef CHESS_SEARCHING_PLAYERBITBOARDS_HPP
#define CHESS_SEARCHING_PLAYERBITBOARDS_HPP

#include "chess/BitBoard.hpp"

namespace chess::searching {

struct PlayerBitBoards {
    BitBoard pieces[6];
    BitBoard occupied;
    BitBoard attack;

    // TODO: move this to .cpp
    friend constexpr bool operator==(const PlayerBitBoards& a, const PlayerBitBoards& b) {
        if (a.occupied != b.occupied)
            return false;

        if (a.attack != b.attack)
            return false;

        for (int i = 0; i < 6; i++)
            if (a.pieces[i] != b.pieces[i])
                return false;

        return true;
    }

    friend constexpr bool operator!=(const PlayerBitBoards& a, const PlayerBitBoards& b) {
        return !(a == b);
    }
};

} // namespace chess::searching

#endif // CHESS_SEARCHING_PLAYERBITBOARDS_HPP
