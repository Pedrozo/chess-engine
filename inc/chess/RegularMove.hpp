#ifndef CHESS_REGULARMOVE_HPP
#define CHESS_REGULARMOVE_HPP

#include "chess/Square.hpp"

namespace chess {

class RegularMove {
public:
    RegularMove(Square from, Square to) : from_(from), to_(to) {}

    Square from() const noexcept {
        return from_;
    }

    Square to() const noexcept {
        return to_;
    }

private:
    Square from_;
    Square to_;
};

} // namespace chess

#endif // CHESS_REGULARMOVE_HPP