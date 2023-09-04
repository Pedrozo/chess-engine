#ifndef CHESS_SEARCH_POSITION_HPP
#define CHESS_SEARCH_POSITION_HPP

#include <optional>

#include "chess/board/SquareCentric.hpp"
#include "chess/board/PieceCentric.hpp"
#include "chess/search/ComputedMove.hpp"
#include "chess/search/BackwardComputedMove.hpp"

namespace chess::search {

class Position {
public:
    const board::SquareCentric& squareCentric() const noexcept {
        return squareCentric_;
    }

    const board::PieceCentric& pieceCentric() const noexcept {
        return pieceCentric_;
    }

    std::optional<PlayerPiece> makeMove(const move::Regular& regularMove);

    void makeMove(const move::Castling& castlingMove);

    void makeMove(const move::EnPassant& enPassantMove);

    std::optional<PlayerPiece> makeMove(const move::Promotion& promotionMove);

    BackwardComputedMove makeMove(const ComputedMove& computedMove);

    void unmakeMove(const BackwardComputedMove& backwardComputedMove);

private:
    board::SquareCentric squareCentric_;
    board::PieceCentric pieceCentric_;
};

} // namespace chess::search

#endif // CHESS_SEARCH_POSITION_HPP
