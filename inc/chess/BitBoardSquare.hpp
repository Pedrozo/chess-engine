#ifndef CHESS_BITBOARDSQUARE_HPP
#define CHESS_BITBOARDSQUARE_HPP

#include <cstdint>

#include "chess/Square.hpp"

namespace chess {

class BitBoardSquare {
public:
    using Type = std::uint64_t;

    constexpr BitBoardSquare(Square square) : bitboard_(1UL << square.index()) {}

    Square square() const;

    constexpr BitBoardSquare operator<<(std::size_t pos) const noexcept {
        return BitBoardSquare(bitboard_ << pos);
    }

    constexpr BitBoardSquare operator>>(std::size_t pos) const noexcept {
        return BitBoardSquare(bitboard_ >> pos);
    }

    constexpr BitBoardSquare& operator<<=(std::size_t pos) noexcept {
        bitboard_ <<= pos;
        return *this;
    }

    constexpr BitBoardSquare& operator>>=(std::size_t pos) noexcept {
        bitboard_ >>= pos;
        return *this;
    }

    template<typename T>
    constexpr T to() const noexcept {
        return static_cast<T>(bitboard_);
    }

private:
    friend class BitBoard;

    constexpr explicit BitBoardSquare(Type bitboard) : bitboard_(bitboard) {}

    Type bitboard_;
};

} // namespace chess

#endif // CHESS_BITBOARDSQUARE_HPP
