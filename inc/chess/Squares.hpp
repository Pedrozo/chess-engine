#ifndef CHESS_SQUARES_HPP
#define CHESS_SQUARES_HPP

#include "chess/Square.hpp"
#include "chess/Direction.hpp"
#include "chess/util/Range.hpp"

namespace chess {

class Squares {
public:
    static constexpr util::Range<Square, Square(*)(Square)> all() noexcept {
        return util::Range<Square, Square(*)(Square)>(a1, h8, east);
    }
};

} // namespace chess

#endif // CHESS_SQUARES_HPP
