#ifndef CHESS_ANTIDIAGONAL_HPP
#define CHESS_ANTIDIAGONAL_HPP

#include <array>

#include "chess/Direction.hpp"
#include "chess/Square.hpp"
#include "chess/BitBoard.hpp"
#include "chess/BitBoardSquare.hpp"
#include "chess/util/Range.hpp"

namespace chess {

class AntiDiagonal {
public:
    static constexpr AntiDiagonal of(Square s) noexcept {
        return AntiDiagonal(s);
    }

    constexpr Square first() const noexcept {
        constexpr std::array<Square, 64> indexes = {
            a1, b1, c1, d1, e1, f1, g1, h1,
            a2, a1, b1, c1, d1, e1, f1, g1,
            a3, a2, a1, b1, c1, d1, e1, f1,
            a4, a3, a2, a1, b1, c1, d1, e1,
            a5, a4, a3, a2, a1, b1, c1, d1,
            a6, a5, a4, a3, a2, a1, b1, c1,
            a7, a6, a5, a4, a3, a2, a1, b1,
            a8, a7, a6, a5, a4, a3, a2, a1
        };

        return indexes[square_];
    }

    constexpr Square last() const noexcept {
        constexpr std::array<Square, 64> indexes = {
            h8, h7, h6, h5, h4, h3, h2, h1,
            g8, h8, h7, h6, h5, h4, h3, h2,
            f8, g8, h8, h7, h6, h5, h4, h3,
            e8, f8, g8, h8, h7, h6, h5, h4,
            d8, e8, f8, g8, h8, h7, h6, h5,
            c8, d8, e8, f8, g8, h8, h7, h6,
            b8, c8, d8, e8, f8, g8, h8, h7,
            a8, b8, c8, d8, e8, f8, g8, h8
        };

        return indexes[square_];
    }

    constexpr BitBoard bitboard() const noexcept {
        constexpr std::array<BitBoard, 64> diagonals = {
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0000008040201008UL), BitBoard(0x0000000080402010UL), BitBoard(0x0000000000804020UL),
            BitBoard(0x0000000000008040UL), BitBoard(0x0000000000000080UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0000008040201008UL), BitBoard(0x0000000080402010UL), BitBoard(0x0000000000804020UL),
            BitBoard(0x0000000000008040UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0000008040201008UL), BitBoard(0x0000000080402010UL), BitBoard(0x0000000000804020UL),
            BitBoard(0x1008040201000000UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0000008040201008UL), BitBoard(0x0000000080402010UL), BitBoard(0x0804020100000000UL),
            BitBoard(0x1008040201000000UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0000008040201008UL), BitBoard(0x0402010000000000UL), BitBoard(0x0804020100000000UL),
            BitBoard(0x1008040201000000UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0000804020100804UL),
            BitBoard(0x0201000000000000UL), BitBoard(0x0402010000000000UL), BitBoard(0x0804020100000000UL),
            BitBoard(0x1008040201000000UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL), BitBoard(0x0080402010080402UL), BitBoard(0x0100000000000000UL),
            BitBoard(0x0201000000000000UL), BitBoard(0x0402010000000000UL), BitBoard(0x0804020100000000UL),
            BitBoard(0x1008040201000000UL), BitBoard(0x2010080402010000UL), BitBoard(0x4020100804020100UL),
            BitBoard(0x8040201008040201UL)
        };

        return diagonals[square_];
    }

    constexpr auto squares() const noexcept {
        return util::Range<Square, Square(*)(Square)>(first(), last(), northeast);
    }

    constexpr auto bitboardSquares() const noexcept {
        return util::Range<BitBoardSquare, BitBoardSquare(*)(BitBoardSquare)>(first(), last(), northeast);
    }

private:
    explicit constexpr AntiDiagonal(Square square) : square_(square) {}

    Square square_;
};

} // namespace chess

#endif // CHESS_ANTIDIAGONAL_HPP
