#ifndef CHESS_MOVE_REGULAR_HPP
#define CHESS_MOVE_REGULAR_HPP

#include "chess/Square.hpp"

namespace chess::move {

class Regular {
public:
    constexpr Regular(Square from, Square to) : from_(from), to_(to) {}

    constexpr Square from() const noexcept {
        return from_;
    }

    constexpr Square to() const noexcept {
        return to_;
    }

private:
    Square from_;
    Square to_;
};

} // namespace chess::move

#endif // CHESS_MOVE_REGULAR_HPP
