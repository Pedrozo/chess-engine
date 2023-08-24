#ifndef CHESS_PLAYERPIECE_HPP
#define CHESS_PLAYERPIECE_HPP

#include "chess/Player.hpp"
#include "chess/Piece.hpp"

namespace chess {

class PlayerPiece {
public:
    constexpr PlayerPiece(Player player, Piece piece)
        : playerPiece_((piece << 1) | player) {}

    constexpr Player player() const noexcept {
        return static_cast<Player>(playerPiece_ & 1);
    }

    constexpr Piece piece() const noexcept {
        return static_cast<Piece>(playerPiece_ >> 1);
    }

    friend constexpr bool operator==(PlayerPiece a, PlayerPiece b) {
        return a.playerPiece_ == b.playerPiece_;
    }

    friend constexpr bool operator!=(PlayerPiece a, PlayerPiece b) {
        return !(a == b);
    }

private:
    int playerPiece_;
};

} // namespace chess

#endif // CHESS_PLAYERPIECE_HPP
