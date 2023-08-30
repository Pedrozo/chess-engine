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
    squares_[castlingMove.targetKingSquare()] = PlayerPiece(castlingMove.player(), Piece::KING);
    squares_[castlingMove.targetRookSquare()] = PlayerPiece(castlingMove.player(), Piece::ROOK);
}

void PositionSquares::makeMove(const EnPassantMove& enPassantMove) {
    squares_[enPassantMove.to()] = squares_[enPassantMove.from()];
    squares_[enPassantMove.from()] = std::nullopt;
    squares_[enPassantMove.captured()] = std::nullopt;
}

void PositionSquares::makeMove(const PromotionMove& promotionMove) {
    squares_[promotionMove.from()] = std::nullopt;
    squares_[promotionMove.to()] = promotionMove.promotedPiece();
}

void PositionSquares::unmakeMove(const RegularMove& regularMove) {
    squares_[regularMove.from()] = squares_[regularMove.to()];
}

void PositionSquares::unmakeMove(const RegularMove& regularMove, PlayerPiece capturedPiece) {    
    unmakeMove(regularMove);
    squares_[regularMove.to()] = capturedPiece;
}

void PositionSquares::unmakeMove(const CastlingMove& castlingMove) {
    squares_[castlingMove.kingSquare()] = PlayerPiece(castlingMove.player(), Piece::KING);
    squares_[castlingMove.rookSquare()] = PlayerPiece(castlingMove.player(), Piece::ROOK);
    squares_[castlingMove.targetKingSquare()] = std::nullopt;
    squares_[castlingMove.targetRookSquare()] = std::nullopt;
}

void PositionSquares::unmakeMove(const EnPassantMove& enPassantMove) {
    squares_[enPassantMove.from()] = squares_[enPassantMove.to()];
    squares_[enPassantMove.to()] = std::nullopt;
    squares_[enPassantMove.captured()] = PlayerPiece(opponent(enPassantMove.player()), Piece::PAWN);
}

void PositionSquares::unmakeMove(const PromotionMove& promotionMove) {
    squares_[promotionMove.from()] = PlayerPiece(promotionMove.promotedPiece().player(), Piece::PAWN);
    squares_[promotionMove.to()] = std::nullopt;
}

} // namespace chess
