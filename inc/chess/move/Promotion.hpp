#ifndef CHESS_MOVE_PROMOTION_HPP
#define CHESS_MOVE_PROMOTION_HPP

#include "chess/Square.hpp"
#include "chess/Piece.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/Direction.hpp"

namespace chess::move {

class Promotion {
public:
    static constexpr bool mayCapture = true;

    constexpr Promotion(Square from, Square to, PlayerPiece promotedPiece)
        : from_(from), to_(to), promotedPiece_(promotedPiece) {}

    constexpr Square from() const noexcept {
        return from_;
    }

    constexpr Square to() const noexcept {
        return to_;
    }

    constexpr PlayerPiece promotedPiece() const noexcept {
        return promotedPiece_;
    }

private:
    Square from_;
    Square to_;
    PlayerPiece promotedPiece_;
};

} // namespace chess::move

#endif // CHESS_MOVE_PROMOTION_HPP
