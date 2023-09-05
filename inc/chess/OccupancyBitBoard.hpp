#ifndef CHESS_OCCUPANCYBITBOARD_HPP
#define CHESS_OCCUPANCYBITBOARD_HPP

#include "chess/BitBoard.hpp"
#include "chess/Square.hpp"
#include "chess/RotatedBitBoard.hpp"
#include "chess/rotation/FileRotation.hpp"
#include "chess/rotation/DiagonalRotation.hpp"
#include "chess/rotation/AntiDiagonalRotation.hpp"

namespace chess {

class OccupancyBitBoard {
public:
    OccupancyBitBoard() : normal_(0UL), fileRotated_(), diagonalRotated_(), antidiagonalRotated_() {}

    explicit OccupancyBitBoard(std::initializer_list<Square> squares) : OccupancyBitBoard() {
        for (Square s : squares)
            set(s);
    }

    BitBoard normal() const noexcept {
        return normal_;
    }

    RotatedBitBoard<rotation::FileRotation> fileRotated() const noexcept {
        return fileRotated_;
    }

    RotatedBitBoard<rotation::DiagonalRotation> diagonalRotated() const noexcept {
        return diagonalRotated_;
    }

    RotatedBitBoard<rotation::AntiDiagonalRotation> antiDiagonalRotated() const noexcept {
        return antidiagonalRotated_;
    }

    void set(Square s) noexcept {
        normal_.set(s);
        fileRotated_.set(s);
        diagonalRotated_.set(s);
        antidiagonalRotated_.set(s);
    }

    void reset(Square s) noexcept {
        normal_.reset(s);
        fileRotated_.reset(s);
        diagonalRotated_.reset(s);
        antidiagonalRotated_.reset(s);
    }

    void flip(Square s) noexcept {
        normal_.flip(s);
        fileRotated_.flip(s);
        diagonalRotated_.flip(s);
        antidiagonalRotated_.flip(s);
    }

    friend bool operator==(const OccupancyBitBoard& a, const OccupancyBitBoard& b) {
        return a.normal_ == b.normal_;
    }

    friend bool operator!=(const OccupancyBitBoard& a, const OccupancyBitBoard& b) {
        return a.normal_ != b.normal_;
    }

private:
    BitBoard normal_;
    RotatedBitBoard<rotation::FileRotation> fileRotated_;
    RotatedBitBoard<rotation::DiagonalRotation> diagonalRotated_;
    RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotated_;
};

} // namespace chess

#endif // CHESS_OCCUPANCYBITBOARD_HPP
