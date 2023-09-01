#ifndef CHESS_UTIL_LOG_HPP
#define CHESS_UTIL_LOG_HPP

#include <cstdio>
#include "chess/BitBoard.hpp"

namespace chess::util {

void log(BitBoard b) {
    std::uint64_t bitboard = b.to<std::uint64_t>();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char c = bool(bitboard & (1L << ((56 - i * 8) + j))) ? '1' : '0';
            printf("%c ", c);
        }

        printf("\n");
    }

    printf("\n");
}

} // namespace chess::util


#endif // CHESS_UTIL_LOG_HPP
