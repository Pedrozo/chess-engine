#ifndef CHESS_OCCUPIEDBITBOARD_HPP
#define CHESS_OCCUPIEDBITBOARD_HPP

#include "chess/BitBoard.hpp"
#include "chess/Square.hpp"
#include "chess/RotatedBitBoard.hpp"
#include "chess/rotation/FileRotation.hpp"
#include "chess/rotation/DiagonalRotation.hpp"
#include "chess/rotation/AntiDiagonalRotation.hpp"

namespace chess {

class OccupiedBitBoard {
public:
    OccupiedBitBoard() : normal_(0UL), fileRotated_(), diagonalRotated_(), antidiagonalRotated_() {}

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

private:
    BitBoard normal_;
    RotatedBitBoard<rotation::FileRotation> fileRotated_;
    RotatedBitBoard<rotation::DiagonalRotation> diagonalRotated_;
    RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotated_;
};

} // namespace chess

#endif // CHESS_OCCUPIEDBITBOARD_HPP
