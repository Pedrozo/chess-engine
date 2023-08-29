#include "chess/PositionSquares.hpp"

namespace chess {

std::optional<PlayerPiece> PositionSquares::makeMove(const RegularMove& regularMove) {
    std::optional<PlayerPiece> captured = squares_[regularMove.to()];
    squares_[regularMove.to()] = squares_[regularMove.from()];
    squares_[regularMove.from()] = std::nullopt;
    return captured;
}

void PositionSquares::makeMove(const CastlingMove& castlingMove) {
    squares_[castlingMove.kingSquare()] = std::nullopt;
    squares_[castlingMove.rookSquare()] = std::nullopt;
    squares_[castlingMove.targetKingSquare()] = std::make_optional(PlayerPiece(castlingMove.player(), Piece::KING));
    squares_[castlingMove.targetRookSquare()] = std::make_optional(PlayerPiece(castlingMove.player(), Piece::ROOK));
}

void PositionSquares::unmakeMove(const RegularMove& regularMove) {
    squares_[regularMove.from()] = squares_[regularMove.to()];
}

void PositionSquares::unmakeMove(const RegularMove& regularMove, PlayerPiece capturedPiece) {    
    unmakeMove(regularMove);
    squares_[regularMove.to()] = capturedPiece;
}

void PositionSquares::unmakeMove(const CastlingMove& castlingMove) {
    squares_[castlingMove.kingSquare()] = std::make_optional(PlayerPiece(castlingMove.player(), Piece::KING));
    squares_[castlingMove.rookSquare()] = std::make_optional(PlayerPiece(castlingMove.player(), Piece::ROOK));
    squares_[castlingMove.targetKingSquare()] = std::nullopt;
    squares_[castlingMove.targetRookSquare()] = std::nullopt;
}

} // namespace chess
