#include "chess/search/Position.hpp"

namespace chess::search {

std::optional<PlayerPiece> Position::makeMove(const move::Regular& regularMove) {
    Player playerInMove = squareCentric_.playerInMove(regularMove);
    PlayerPiece movedPiece = squareCentric_.at(regularMove.from()).value();
    std::optional<PlayerPiece> captured = squareCentric_.makeMove(regularMove);

    if (captured.has_value()) {
        pieceCentric_.makeMove(regularMove, movedPiece, captured.value());
    } else {
        pieceCentric_.makeMove(regularMove, movedPiece);
    }

    countRepetition(playerInMove, pieceCentric_);

    return captured;
}

void Position::makeMove(const move::Castling& castlingMove) {
    Player playerInMove = squareCentric_.playerInMove(castlingMove);
    squareCentric_.makeMove(castlingMove);
    pieceCentric_.makeMove(castlingMove);

    countRepetition(playerInMove, pieceCentric_);
}

void Position::makeMove(const move::EnPassant& enPassantMove) {
    Player playerInMove = squareCentric_.playerInMove(enPassantMove);
    squareCentric_.makeMove(enPassantMove);
    pieceCentric_.makeMove(enPassantMove);

    countRepetition(playerInMove, pieceCentric_);
}

std::optional<PlayerPiece> Position::makeMove(const move::Promotion& promotionMove) {
    Player playerInMove = squareCentric_.playerInMove(promotionMove);
    std::optional<PlayerPiece> captured = squareCentric_.makeMove(promotionMove);

    if (captured.has_value()) {
        pieceCentric_.makeMove(promotionMove, captured.value());
    } else {
        pieceCentric_.makeMove(promotionMove);
    }

    countRepetition(playerInMove, pieceCentric_);

    return captured;
}

BackwardComputedMove Position::makeMove(const ComputedMove& computedMove) {
    Player playerInMove = squareCentric_.playerInMove(computedMove.move());
    std::optional<PlayerPiece> captured = std::visit(squareCentric_.visitor(), computedMove.move());
    BackwardComputedMove backwardComputedMove(move::toBackward(computedMove.move()), pieceCentric_, captured);

    pieceCentric_ = computedMove.pieceCentricBoard();
    countRepetition(playerInMove, pieceCentric_);
    return backwardComputedMove;
}

void Position::unmakeMove(const BackwardComputedMove& backwardComputedMove) {
    Player playerInMove = squareCentric_.playerInMove(backwardComputedMove.backwardMove());
    std::visit(squareCentric_.visitor(), backwardComputedMove.backwardMove());
    discountRepetion(playerInMove, pieceCentric_);
    pieceCentric_ = backwardComputedMove.previousPieceCentricBoard();
}

std::size_t Position::repetitionCount(Player playerInMove, const board::PieceCentric& board) const {
    auto pos = repeatedPositionCount_[playerInMove].find(board);

    if (pos == repeatedPositionCount_[playerInMove].end())
        return std::size_t(0);

    return pos->second;
}

} // namespace chess::search
