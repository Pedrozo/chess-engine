#ifndef CHESS_DIAGONAL_HPP
#define CHESS_DIAGONAL_HPP

#include <array>

#include "chess/BitBoard.hpp"
#include "chess/BitBoardSquare.hpp"
#include "chess/Direction.hpp"
#include "chess/Square.hpp"
#include "chess/util/Range.hpp"

namespace chess {

class Diagonal {
public:
    static constexpr Diagonal of(Square s) noexcept {
        return Diagonal(s);
    }

    constexpr Square first() const noexcept {
        constexpr std::array<Square, 64> indexes = {
            a1, b1, c1, d1, e1, f1, g1, h1,
            b1, c1, d1, e1, f1, g1, h1, h2,
            c1, d1, e1, f1, g1, h1, h2, h3,
            d1, e1, f1, g1, h1, h2, h3, h4,
            e1, f1, g1, h1, h2, h3, h4, h5,
            f1, g1, h1, h2, h3, h4, h5, h6,
            g1, h1, h2, h3, h4, h5, h6, h7,
            h1, h2, h3, h4, h5, h6, h7, h8
        };

        return indexes[square_];
    }

    constexpr Square last() const noexcept {
        constexpr std::array<Square, 64> indexes = {
            a1, a2, a3, a4, a5, a6, a7, a8,
            a2, a3, a4, a5, a6, a7, a8, b8,
            a3, a4, a5, a6, a7, a8, b8, c8,
            a4, a5, a6, a7, a8, b8, c8, d8,
            a5, a6, a7, a8, b8, c8, d8, e8,
            a6, a7, a8, b8, c8, d8, e8, f8,
            a7, a8, b8, c8, d8, e8, f8, g8,
            a8, b8, c8, d8, e8, f8, g8, h8
        };

        return indexes[square_];
    }

    constexpr BitBoard bitboard() const noexcept {
        constexpr std::array<BitBoard, 64> diagonals = {
            BitBoard(0x0000000000000001UL), BitBoard(0x0000000000000102UL), BitBoard(0x0000000000010204UL),
            BitBoard(0x0000000001020408UL), BitBoard(0x0000000102040810UL), BitBoard(0x0000010204081020UL),
            BitBoard(0x0001020408102040UL), BitBoard(0x0102040810204080UL), BitBoard(0x0000000000000102UL),
            BitBoard(0x0000000000010204UL), BitBoard(0x0000000001020408UL), BitBoard(0x0000000102040810UL),
            BitBoard(0x0000010204081020UL), BitBoard(0x0001020408102040UL), BitBoard(0x0102040810204080UL),
            BitBoard(0x0204081020408000UL), BitBoard(0x0000000000010204UL), BitBoard(0x0000000001020408UL),
            BitBoard(0x0000000102040810UL), BitBoard(0x0000010204081020UL), BitBoard(0x0001020408102040UL),
            BitBoard(0x0102040810204080UL), BitBoard(0x0204081020408000UL), BitBoard(0x0408102040800000UL),
            BitBoard(0x0000000001020408UL), BitBoard(0x0000000102040810UL), BitBoard(0x0000010204081020UL),
            BitBoard(0x0001020408102040UL), BitBoard(0x0102040810204080UL), BitBoard(0x0204081020408000UL),
            BitBoard(0x0408102040800000UL), BitBoard(0x0810204080000000UL), BitBoard(0x0000000102040810UL),
            BitBoard(0x0000010204081020UL), BitBoard(0x0001020408102040UL), BitBoard(0x0102040810204080UL),
            BitBoard(0x0204081020408000UL), BitBoard(0x0408102040800000UL), BitBoard(0x0810204080000000UL),
            BitBoard(0x1020408000000000UL), BitBoard(0x0000010204081020UL), BitBoard(0x0001020408102040UL),
            BitBoard(0x0102040810204080UL), BitBoard(0x0204081020408000UL), BitBoard(0x0408102040800000UL),
            BitBoard(0x0810204080000000UL), BitBoard(0x1020408000000000UL), BitBoard(0x2040800000000000UL),
            BitBoard(0x0001020408102040UL), BitBoard(0x0102040810204080UL), BitBoard(0x0204081020408000UL),
            BitBoard(0x0408102040800000UL), BitBoard(0x0810204080000000UL), BitBoard(0x1020408000000000UL),
            BitBoard(0x2040800000000000UL), BitBoard(0x4080000000000000UL), BitBoard(0x0102040810204080UL),
            BitBoard(0x0204081020408000UL), BitBoard(0x0408102040800000UL), BitBoard(0x0810204080000000UL),
            BitBoard(0x1020408000000000UL), BitBoard(0x2040800000000000UL), BitBoard(0x4080000000000000UL),
            BitBoard(0x8000000000000000UL)
        };

        return diagonals[square_];
    }

    constexpr auto squares() const noexcept {
        return util::Range<Square, Square(*)(Square)>(first(), last(), northwest);
    }

    constexpr auto bitboardSquares() const noexcept {
        return util::Range<BitBoardSquare, BitBoardSquare(*)(BitBoardSquare)>(first(), last(), northwest);
    }

private:
    explicit constexpr Diagonal(Square square) : square_(square) {}

    Square square_;
};

} // namespace chess

#endif // CHESS_DIAGONAL_HPP
