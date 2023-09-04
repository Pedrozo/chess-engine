#include "chess/board/PositionSquares.hpp"

namespace chess::board {

PositionSquares::PositionSquares(std::initializer_list<std::pair<Square, PlayerPiece>> pieces) : squares_() {
    for (const auto& squarePiece : pieces)
        squares_[squarePiece.first] = squarePiece.second;
}

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

void PositionSquares::unmakeMove(const move::Backward<move::Regular>& backwardRegularMove) {
    squares_[backwardRegularMove.move().from()] = squares_[backwardRegularMove.move().to()];
    squares_[backwardRegularMove.move().to()] = backwardRegularMove.captured();
}

void PositionSquares::unmakeMove(const move::Backward<move::Castling>& backwardCastlingMove) {
    squares_[backwardCastlingMove.move().kingSquare()] = PlayerPiece(backwardCastlingMove.move().player(), Piece::KING);
    squares_[backwardCastlingMove.move().rookSquare()] = PlayerPiece(backwardCastlingMove.move().player(), Piece::ROOK);
    squares_[backwardCastlingMove.move().targetKingSquare()] = std::nullopt;
    squares_[backwardCastlingMove.move().targetRookSquare()] = std::nullopt;
}

void PositionSquares::unmakeMove(const move::Backward<move::EnPassant>& backwardEnPassantMove) {
    squares_[backwardEnPassantMove.move().from()] = squares_[backwardEnPassantMove.move().to()];
    squares_[backwardEnPassantMove.move().to()] = std::nullopt;
    squares_[backwardEnPassantMove.move().captured()] = PlayerPiece(opponent(backwardEnPassantMove.move().player()), Piece::PAWN);
}

void PositionSquares::unmakeMove(const move::Backward<move::Promotion>& backwardPromotionMove) {
    squares_[backwardPromotionMove.move().from()] = PlayerPiece(backwardPromotionMove.move().promotedPiece().player(), Piece::PAWN);
    squares_[backwardPromotionMove.move().to()] = backwardPromotionMove.captured();
}

} // namespace chess::board
