#ifndef CHESS_BITBOARD_HPP
#define CHESS_BITBOARD_HPP

#include <cstdint>
#include <initializer_list>
#include "chess/BitBoardSquare.hpp"

namespace chess {

class BitBoard {
public:
    using Type = std::uint64_t;

    class Iterator;

    constexpr BitBoard() : bitboard_() {}

    explicit constexpr BitBoard(std::initializer_list<Square> squares) : bitboard_(0) {
        for (Square square : squares)
            set(square);
    }

    template<typename T>
    explicit constexpr BitBoard(T bitboard) : bitboard_(static_cast<Type>(bitboard)) {}

    constexpr BitBoard(BitBoardSquare bitboard) : bitboard_(bitboard.to<Type>()) {}

    constexpr void set(Square square) noexcept {
        *this |= BitBoardSquare(square);
    }

    constexpr void reset(Square square) noexcept {
        *this &= ~BitBoard(BitBoardSquare(square));
    }

    constexpr void flip(Square square) noexcept {
        *this ^= BitBoardSquare(square);
    }

    constexpr bool isEmpty() const noexcept {
        return bitboard_ == 0UL;
    }

    constexpr BitBoard operator~() const noexcept {
        return BitBoard(~bitboard_);
    }

    constexpr BitBoard operator-() const noexcept {
        return BitBoard(-bitboard_);
    }

    constexpr BitBoard operator<<(std::size_t pos) const {
        return BitBoard(bitboard_ << pos);
    }

    constexpr BitBoard operator>>(std::size_t pos) const {
        return BitBoard(bitboard_ >> pos);
    }

    constexpr BitBoard& operator<<=(std::size_t pos) {
        bitboard_ <<= pos;
        return *this;
    }

    constexpr BitBoard& operator>>=(std::size_t pos) {
        bitboard_ >>= pos;
        return *this;
    }

    constexpr BitBoard& operator&=(BitBoard b) {
        bitboard_ &= b.bitboard_;
        return *this;
    }

    constexpr BitBoard& operator|=(BitBoard b) {
        bitboard_ |= b.bitboard_;
        return *this;
    }

    constexpr BitBoard& operator^=(BitBoard b) {
        bitboard_ ^= b.bitboard_;
        return *this;
    }

    constexpr Iterator begin() const noexcept;

    constexpr Iterator end() const noexcept;

    template<typename T>
    constexpr T to() const {
        return static_cast<T>(bitboard_);
    }

private:
    Type bitboard_;
};

constexpr inline bool operator==(BitBoard a, BitBoard b) {
    return a.to<BitBoard::Type>() == b.to<BitBoard::Type>();
}

constexpr inline bool operator!=(BitBoard a, BitBoard b) {
    return !(a == b);
}

constexpr inline BitBoard operator|(BitBoard a, BitBoard b) {
    return BitBoard(a.to<BitBoard::Type>() | b.to<BitBoard::Type>());
}

constexpr inline BitBoard operator&(BitBoard a, BitBoard b) {
    return BitBoard(a.to<BitBoard::Type>() & b.to<BitBoard::Type>());
}

constexpr inline BitBoard operator^(BitBoard a, BitBoard b) {
    return BitBoard(a.to<BitBoard::Type>() ^ b.to<BitBoard::Type>());
}

class BitBoard::Iterator {
public:
    explicit constexpr Iterator(BitBoard b) : bitboard_(b) {}

    constexpr BitBoardSquare operator*() const noexcept {
        BitBoard b = bitboard_ & -bitboard_;
        return BitBoardSquare(b.to<BitBoardSquare::Type>());
    }

    constexpr void operator++() noexcept {
        bitboard_ &= ~(bitboard_ & -bitboard_);
    }

    friend constexpr bool operator==(BitBoard::Iterator a, BitBoard::Iterator b) {
        return a.bitboard_ == b.bitboard_;
    }

    friend constexpr bool operator!=(BitBoard::Iterator a, BitBoard::Iterator b) {
        return !(a == b);
    }

private:
    BitBoard bitboard_;
};

constexpr BitBoard::Iterator BitBoard::begin() const noexcept {
    return BitBoard::Iterator(*this);
}

constexpr BitBoard::Iterator BitBoard::end() const noexcept {
    return BitBoard::Iterator(BitBoard(0UL));
}

} // namespace chess

#endif // CHESS_BITBOARD_HPP
