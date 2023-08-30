#ifndef CHESS_PROMOTIONMOVE_HPP
#define CHESS_PROMOTIONMOVE_HPP

#include "chess/Square.hpp"
#include "chess/Piece.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/Direction.hpp"

namespace chess {

class PromotionMove {
public:
    constexpr PromotionMove(Square from, Square to, PlayerPiece promotedPiece)
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

} // namespace chess


#endif // CHESS_PROMOTIONMOVE_HPP
