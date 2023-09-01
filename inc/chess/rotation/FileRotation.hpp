#ifndef CHESS_ROTATION_FILEROTATION_HPP
#define CHESS_ROTATION_FILEROTATION_HPP

#include "chess/Square.hpp"
#include "chess/File.hpp"

namespace chess::rotation {

class FileRotation {
public:
    // TODO: constexpr it?
    static Square rotate(Square s) noexcept {
        return Square(computed().rotated[s]);
    }

    static std::size_t shift(Square s) noexcept {
        std::size_t fileIndex = File::of(s).first().index() - File::left().first().index();
        return fileIndex << 3;
    }

private:
    struct PreComputed {
        constexpr PreComputed() : rotated() {
            for (std::size_t i = 0; i < 64; i++)
                rotated[i] = ((i & 7) << 3) | (i >> 3);
        }

        std::size_t rotated[64];
    };

    static const PreComputed& computed() noexcept {
        static const PreComputed c;
        return c;
    }
};

} // namespace chess::rotation

#endif // CHESS_ROTATION_FILEROTATION_HPP
