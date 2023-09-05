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
    Position(ForwardIt begin, ForwardIt end, Player firstPlayerInMove = Player::WHITE)
        : squareCentric_(begin, end), pieceCentric_(begin, end), repeatedPositionCount_() {
        countRepetition(firstPlayerInMove, pieceCentric_);
    }

    explicit Position(std::initializer_list<std::pair<Square, PlayerPiece>> pieces, Player firstPlayerInMove = Player::WHITE)
        : Position(pieces.begin(), pieces.end(), firstPlayerInMove) {}

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

    std::size_t repetitionCount(Player playerInMove, const board::PieceCentric& board) const;

private:
    void countRepetition(Player playerInMove, const board::PieceCentric& board) {
        ++repeatedPositionCount_[playerInMove][board];
    }

    void discountRepetion(Player playerInMove, const board::PieceCentric& board) {
        --repeatedPositionCount_[playerInMove][board];
    }

    board::SquareCentric squareCentric_;
    board::PieceCentric pieceCentric_;
    std::array<std::unordered_map<board::PieceCentric, std::size_t>, 2> repeatedPositionCount_;
};

} // namespace chess::search

#endif // CHESS_SEARCH_POSITION_HPP
