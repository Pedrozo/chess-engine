#ifndef CHESS_UTIL_MAKEBITBOARD_HPP
#define CHESS_UTIL_MAKEBITBOARD_HPP

#include "chess/BitBoard.hpp"
#include "chess/Direction.hpp"
#include "chess/File.hpp"

namespace chess::util {

inline constexpr BitBoard makeBitBoard(std::initializer_list<int> bits) {
    BitBoard r(0);
    BitBoardSquare b(a8);

    for (int bit : bits) {
        if (bit != 0)
            r |= b;

        if ((b & File::right().bitboard()).isEmpty())
            b = east(b);
        else
            b = south(west(b, 7));
    }

    return r;
}

} // namespace chess::util

#endif // CHESS_UTIL_MAKEBITBOARD_HPP
