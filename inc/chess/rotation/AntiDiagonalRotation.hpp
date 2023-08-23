#ifndef CHESS_ROTATION_ANTIDIAGONALROTATION_HPP
#define CHESS_ROTATION_ANTIDIAGONALROTATION_HPP

#include "chess/Square.hpp"
#include "chess/AntiDiagonal.hpp"

namespace chess::rotation {

class AntiDiagonalRotation {
public:
    static Square rotate(Square s) noexcept {
        return Square(computed().rotated[s]);
    }

    static std::size_t shift(Square s) noexcept {
        return computed().shift[s];
    }

private:
    struct PreComputed {
        PreComputed() : rotated(), shift() {
            constexpr std::array<Square, 15> startingSquares = {
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, a3, a4, a5, a6, a7, a8
            };

            std::size_t index = 0;

            for (Square antiDiagonalStart : startingSquares) {
                std::size_t sft = index;

                for (Square s : AntiDiagonal::of(antiDiagonalStart).squares()) {
                    rotated[s] = Square(index);
                    shift[s] = sft;
                    ++index;
                }
            }
        }

        std::size_t rotated[64];
        std::size_t shift[64];
    };

    static const PreComputed& computed() noexcept {
        static const PreComputed c;
        return c;
    }
};

} // namespace chess::rotation

#endif // CHESS_ROTATION_ANTIDIAGONALROTATION_HPP
