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

constexpr PlayerPiece WHITE_KING = PlayerPiece(WHITE, KING);

constexpr PlayerPiece WHITE_QUEEN = PlayerPiece(WHITE, QUEEN);

constexpr PlayerPiece WHITE_ROOK = PlayerPiece(WHITE, ROOK);

constexpr PlayerPiece WHITE_BISHOP = PlayerPiece(WHITE, BISHOP);

constexpr PlayerPiece WHITE_KNIGHT = PlayerPiece(WHITE, KNIGHT);

constexpr PlayerPiece WHITE_PAWN = PlayerPiece(WHITE, PAWN);

constexpr PlayerPiece BLACK_KING = PlayerPiece(BLACK, KING);

constexpr PlayerPiece BLACK_QUEEN = PlayerPiece(BLACK, QUEEN);

constexpr PlayerPiece BLACK_ROOK = PlayerPiece(BLACK, ROOK);

constexpr PlayerPiece BLACK_BISHOP = PlayerPiece(BLACK, BISHOP);

constexpr PlayerPiece BLACK_KNIGHT = PlayerPiece(BLACK, KNIGHT);

constexpr PlayerPiece BLACK_PAWN = PlayerPiece(BLACK, PAWN);

} // namespace chess

#endif // CHESS_PLAYERPIECE_HPP
