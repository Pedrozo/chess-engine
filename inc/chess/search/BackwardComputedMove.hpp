#ifndef CHESS_SEARCH_BACKWARDCOMPUTEDMOVE_HPP
#define CHESS_SEARCH_BACKWARDCOMPUTEDMOVE_HPP

#include <optional>

#include "chess/move/AnyBackward.hpp"
#include "chess/board/PieceCentric.hpp"

namespace chess::search {

class BackwardComputedMove {
public:
    BackwardComputedMove(
        move::AnyBackward backwardMove, board::PieceCentric previousBoard, std::optional<PlayerPiece> captured = std::nullopt)
        : backwardMove_(backwardMove), previousBoard_(previousBoard), captured_(captured) {}

    const move::AnyBackward& backwardMove() const noexcept {
        return backwardMove_;
    }

    const board::PieceCentric& previousPieceCentricBoard() const noexcept {
        return previousBoard_;
    }

    std::optional<PlayerPiece> capturedPiece() const noexcept {
        return captured_;
    }

private:
    move::AnyBackward backwardMove_;
    board::PieceCentric previousBoard_;
    std::optional<PlayerPiece> captured_;
};

} // namespace chess:search

#endif // CHESS_SEARCH_BACKWARDCOMPUTEDMOVE_HPP
