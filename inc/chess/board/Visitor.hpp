#ifndef CHESS_BOARD_VISITOR_HPP
#define CHESS_BOARD_VISITOR_HPP

#include <type_traits>
#include <optional>
#include "chess/PlayerPiece.hpp"

namespace chess::board {

template<typename BoardRepresentation>
class Visitor {
public:
    explicit Visitor(BoardRepresentation& board) : board_(board) {}

    template<typename T>
    auto operator()(const T& move) -> std::enable_if_t<T::mayCapture, std::optional<PlayerPiece>> {
        return board_.makeMove(move);
    }

    template<typename T>
    auto operator()(const T& move) -> std::enable_if_t<!T::mayCapture, std::optional<PlayerPiece>> {
        board_.makeMove(move);
        return std::nullopt;
    }

    template<typename T>
    void operator()(const move::Backward<T>& backwardMove) {
        board_.unmakeMove(backwardMove);
    }

private:
    BoardRepresentation& board_;
};

} // namespace chess::board

#endif // CHESS_BOARD_VISITOR_HPP
