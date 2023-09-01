#ifndef CHESS_FILE_HPP
#define CHESS_FILE_HPP

#include "chess/BitBoard.hpp"
#include "chess/BitBoardSquare.hpp"
#include "chess/Direction.hpp"
#include "chess/Square.hpp"
#include "chess/util/Range.hpp"

namespace chess {

class File {
public:
    static constexpr File left() noexcept {
        return File(a1);
    }

    static constexpr File right() noexcept {
        return File(h1);
    }

    static constexpr File of(Square s) noexcept {
        return File(Square(s.index() & 7));
    }

    constexpr Square first() const noexcept {
        return first_;
    }

    constexpr Square last() const noexcept {
        return Square(first_.index() + 56);
    }

    constexpr BitBoard bitboard() const noexcept {
        constexpr BitBoard firstFile(0x101010101010101UL);
        return firstFile << first_.index();
    }

    constexpr auto squares() const noexcept {
        return util::Range<Square, Square(*)(Square)>(first_, Square(first_.index() + 8 * 7), north);
    }

    constexpr auto bitboardSquares() const noexcept {
        return util::Range<BitBoardSquare, BitBoardSquare(*)(BitBoardSquare)>(
            BitBoardSquare(first_), BitBoardSquare(first_) << (8 * 7), north);
    }

private:
    explicit constexpr File(Square first) : first_(first) {}

    Square first_;
};

} // namespace chess

#endif // CHESS_FILE_HPP
