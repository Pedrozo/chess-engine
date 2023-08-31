#include "chess/PositionSquares.hpp"

namespace chess {

std::optional<PlayerPiece> PositionSquares::makeMove(const move::Regular& regularMove) {
    std::optional<PlayerPiece> captured = squares_[regularMove.to()];
    squares_[regularMove.to()] = squares_[regularMove.from()];
    squares_[regularMove.from()] = std::nullopt;
    return captured;
}

void PositionSquares::makeMove(const move::Castling& castlingMove) {
    squares_[castlingMove.kingSquare()] = std::nullopt;
    squares_[castlingMove.rookSquare()] = std::nullopt;
    squares_[castlingMove.targetKingSquare()] = PlayerPiece(castlingMove.player(), Piece::KING);
    squares_[castlingMove.targetRookSquare()] = PlayerPiece(castlingMove.player(), Piece::ROOK);
}

void PositionSquares::makeMove(const move::EnPassant& enPassantMove) {
    squares_[enPassantMove.to()] = squares_[enPassantMove.from()];
    squares_[enPassantMove.from()] = std::nullopt;
    squares_[enPassantMove.captured()] = std::nullopt;
}

std::optional<PlayerPiece> PositionSquares::makeMove(const move::Promotion& promotionMove) {
    std::optional<PlayerPiece> captured = squares_[promotionMove.to()];
    squares_[promotionMove.from()] = std::nullopt;
    squares_[promotionMove.to()] = promotionMove.promotedPiece();
    return captured;
}

void PositionSquares::unmakeMove(const move::Regular& regularMove) {
    squares_[regularMove.from()] = squares_[regularMove.to()];
}

void PositionSquares::unmakeMove(const move::Regular& regularMove, PlayerPiece capturedPiece) {    
    unmakeMove(regularMove);
    squares_[regularMove.to()] = capturedPiece;
}

void PositionSquares::unmakeMove(const move::Castling& castlingMove) {
    squares_[castlingMove.kingSquare()] = PlayerPiece(castlingMove.player(), Piece::KING);
    squares_[castlingMove.rookSquare()] = PlayerPiece(castlingMove.player(), Piece::ROOK);
    squares_[castlingMove.targetKingSquare()] = std::nullopt;
    squares_[castlingMove.targetRookSquare()] = std::nullopt;
}

void PositionSquares::unmakeMove(const move::EnPassant& enPassantMove) {
    squares_[enPassantMove.from()] = squares_[enPassantMove.to()];
    squares_[enPassantMove.to()] = std::nullopt;
    squares_[enPassantMove.captured()] = PlayerPiece(opponent(enPassantMove.player()), Piece::PAWN);
}

void PositionSquares::unmakeMove(const move::Promotion& promotionMove) {
    squares_[promotionMove.from()] = PlayerPiece(promotionMove.promotedPiece().player(), Piece::PAWN);
    squares_[promotionMove.to()] = std::nullopt;
}

} // namespace chess
