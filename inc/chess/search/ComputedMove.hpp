#ifndef CHESS_SEARCH_COMPUTEDMOVE_HPP
#define CHESS_SEARCH_COMPUTEDMOVE_HPP

#include "chess/move/Any.hpp"
#include "chess/board/PieceCentric.hpp"

namespace chess::search {

class ComputedMove {
public:
    ComputedMove(move::Any move, board::PieceCentric computedPieceCentric)
        : move_(move), computedPieceCentric_(std::move(computedPieceCentric)) {}

    const move::Any& move() const noexcept {
        return move_;
    }

    const board::PieceCentric& pieceCentricBoard() const noexcept {
        return computedPieceCentric_;
    }

private:
    move::Any move_;
    board::PieceCentric computedPieceCentric_;
};

} // namespace chess::search

#endif // CHESS_SEARCH_COMPUTEDMOVE_HPP
