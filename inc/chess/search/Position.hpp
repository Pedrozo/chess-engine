#ifndef CHESS_SEARCH_POSITION_HPP
#define CHESS_SEARCH_POSITION_HPP

#include <optional>
#include <unordered_map>

#include "chess/board/SquareCentric.hpp"
#include "chess/board/PieceCentric.hpp"
#include "chess/search/ComputedMove.hpp"
#include "chess/search/BackwardComputedMove.hpp"

namespace chess::search {

class Position {
public:
    template<typename ForwardIt>
    Position(ForwardIt begin, ForwardIt end)
        : squareCentric_(begin, end), pieceCentric_(begin, end), repeatedPositionCount_() {
        countRepetition(pieceCentric_);
    }

    explicit Position(std::initializer_list<std::pair<Square, PlayerPiece>> pieces)
        : Position(pieces.begin(), pieces.end()) {}

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

    std::size_t repetitionCount(const board::PieceCentric& board) const;

private:
    void countRepetition(const board::PieceCentric& board) {
        ++repeatedPositionCount_[board];
    }

    void discountRepetion(const board::PieceCentric& board) {
        --repeatedPositionCount_[board];
    }

    board::SquareCentric squareCentric_;
    board::PieceCentric pieceCentric_;
    std::unordered_map<board::PieceCentric, std::size_t> repeatedPositionCount_;
};

} // namespace chess::search

#endif // CHESS_SEARCH_POSITION_HPP
