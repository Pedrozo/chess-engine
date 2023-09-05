#include "chess/search/Position.hpp"

namespace chess::search {

std::optional<PlayerPiece> Position::makeMove(const move::Regular& regularMove) {
    PlayerPiece movedPiece = squareCentric_.at(regularMove.from()).value();
    std::optional<PlayerPiece> captured = squareCentric_.makeMove(regularMove);

    if (captured.has_value()) {
        pieceCentric_.makeMove(regularMove, movedPiece, captured.value());
    } else {
        pieceCentric_.makeMove(regularMove, movedPiece);
    }

    countRepetition(pieceCentric_);

    return captured;
}

void Position::makeMove(const move::Castling& castlingMove) {
    squareCentric_.makeMove(castlingMove);
    pieceCentric_.makeMove(castlingMove);

    countRepetition(pieceCentric_);
}

void Position::makeMove(const move::EnPassant& enPassantMove) {
    squareCentric_.makeMove(enPassantMove);
    pieceCentric_.makeMove(enPassantMove);

    countRepetition(pieceCentric_);
}

std::optional<PlayerPiece> Position::makeMove(const move::Promotion& promotionMove) {
    std::optional<PlayerPiece> captured = squareCentric_.makeMove(promotionMove);

    if (captured.has_value()) {
        pieceCentric_.makeMove(promotionMove, captured.value());
    } else {
        pieceCentric_.makeMove(promotionMove);
    }

    countRepetition(pieceCentric_);

    return captured;
}

BackwardComputedMove Position::makeMove(const ComputedMove& computedMove) {
    std::optional<PlayerPiece> captured = std::visit(squareCentric_.visitor(), computedMove.move());
    BackwardComputedMove backwardComputedMove(move::toBackward(computedMove.move()), pieceCentric_, captured);
    
    pieceCentric_ = computedMove.pieceCentricBoard();

    countRepetition(pieceCentric_);

    return backwardComputedMove;
}

void Position::unmakeMove(const BackwardComputedMove& backwardComputedMove) {
    std::visit(squareCentric_.visitor(), backwardComputedMove.backwardMove());
    discountRepetion(pieceCentric_);
    pieceCentric_ = backwardComputedMove.previousPieceCentricBoard();
}

std::size_t Position::repetitionCount(const board::PieceCentric& board) const {
    auto pos = repeatedPositionCount_.find(board);

    if (pos == repeatedPositionCount_.end())
        return std::size_t(0);

    return pos->second;
}

} // namespace chess::search
