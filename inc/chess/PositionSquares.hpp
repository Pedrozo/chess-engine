#ifndef CHESS_POSITIONSQUARES_HPP
#define CHESS_POSITIONSQUARES_HPP

#include "chess/Square.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/move/Regular.hpp"
#include "chess/move/Castling.hpp"
#include "chess/move/EnPassant.hpp"
#include "chess/move/Promotion.hpp"

#include <optional>

namespace chess {

class PositionSquares {
public:
    explicit PositionSquares(std::initializer_list<std::pair<Square, PlayerPiece>> pieces);

    std::optional<PlayerPiece> at(Square square) const {
        return squares_[square];
    }

    std::optional<PlayerPiece> makeMove(const move::Regular& regularMove);

    void makeMove(const move::Castling& castlingMove);

    void makeMove(const move::EnPassant& enPassantMove);

    std::optional<PlayerPiece> makeMove(const move::Promotion& promotionMove);

    void unmakeMove(const move::Regular& regularMove);

    void unmakeMove(const move::Regular& regularMove, PlayerPiece capturedPiece);

    void unmakeMove(const move::Castling& castlingMove);

    void unmakeMove(const move::EnPassant& enPassantMove);

    void unmakeMove(const move::Promotion& promotionMove);

private:
    std::optional<PlayerPiece> squares_[64];
};

} // namespace chess

#endif // CHESS_POSITIONSQUARES_HPP
