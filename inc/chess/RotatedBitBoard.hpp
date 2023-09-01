#ifndef CHESS_ROTATEDBITBOARD_HPP
#define CHESS_ROTATEDBITBOARD_HPP

#include "chess/BitBoard.hpp"
#include "chess/Rank.hpp"

namespace chess {

template<typename RotationPolicy>
class RotatedBitBoard {
public:
    constexpr RotatedBitBoard() : bitboard_(0UL) {}

    constexpr void set(Square s) noexcept {
        bitboard_.set(RotationPolicy::rotate(s));
    }

    constexpr void reset(Square s) noexcept {
        bitboard_.reset(RotationPolicy::rotate(s));
    }

    constexpr void flip(Square s) noexcept {
        bitboard_.flip(RotationPolicy::rotate(s));
    }

    constexpr BitBoard bitboard() const noexcept {
        return bitboard_;
    }

    constexpr std::size_t line(Square s) const noexcept {
        BitBoard b = ((bitboard_ >> RotationPolicy::shift(s)) & Rank::bottom().bitboard());
        return b.to<std::size_t>();
    }

private:
    BitBoard bitboard_;
};

} // namespace chess

#endif // CHESS_ROTATEDBITBOARD_HPP
