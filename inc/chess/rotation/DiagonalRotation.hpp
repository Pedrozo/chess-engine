#ifndef CHESS_ROTATION_DIAGONALROTATION_HPP
#define CHESS_ROTATION_DIAGONALROTATION_HPP

#include "chess/Square.hpp"
#include "chess/Diagonal.hpp"

namespace chess::rotation {

class DiagonalRotation {
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
                h2, h3, h4, h5, h6, h7, h8
            };

            std::size_t index = 0;

            for (Square diagonalStart : startingSquares) {
                std::size_t sft = index;

                for (Square s : Diagonal::of(diagonalStart).squares()) {
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

#endif // CHESS_ROTATION_DIAGONALROTATION_HPP
