#include <stdexcept>

#include "chess/BitBoardSquare.hpp"
#include "chess/BitBoard.hpp"
#include "chess/Rank.hpp"

namespace chess {

struct ComputedSquares {
    constexpr ComputedSquares() : square() {
        for (std::size_t i = 0, s = 1; s < 256; i++, s <<= 1)
            square[s] = i;
    }

    std::size_t square[256];
};

Square BitBoardSquare::square() const {
    static ComputedSquares computed;

    std::size_t offset = 0;

    BitBoardSquare b = *this;

    while ((b & Rank::bottom().bitboard()).isEmpty()) {
        offset += 8;
        b = south(b);
    }

    return Square(computed.square[b.to<std::size_t>()] + offset);
}

} // namespace chess
