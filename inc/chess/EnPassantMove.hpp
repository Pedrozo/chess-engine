#ifndef CHESS_ENPASSANTMOVE_HPP
#define CHESS_ENPASSANTMOVE_HPP

#include "chess/Square.hpp"
#include "chess/Direction.hpp"

namespace chess {

class EnPassantMove {
public:
    constexpr EnPassantMove(Square from, Square to)
        : from_(from), to_(to), player_(from_.index() < to_.index() ? Player::WHITE : Player::BLACK) {}

    constexpr Player player() const noexcept {
        return player_;
    }

    constexpr Square from() const noexcept {
        return from_;
    }

    constexpr Square to() const noexcept {
        return to_;
    }

    constexpr Square captured() const noexcept {
        return player_ == Player::WHITE ? south(to_) : north(to_);
    }

private:
    Square from_;
    Square to_;
    Player player_;
};

} // namespace chess

#endif // CHESS_ENPASSANTMOVE_HPP
