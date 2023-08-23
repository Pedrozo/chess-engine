#ifndef CHESS_RANK_HPP
#define CHESS_RANK_HPP

#include "chess/BitBoard.hpp"
#include "chess/BitBoardSquare.hpp"
#include "chess/Direction.hpp"
#include "chess/Square.hpp"
#include "chess/util/Range.hpp"

namespace chess {

class Rank {
public:
    static constexpr Rank top() noexcept {
        return Rank(a8);
    }

    static constexpr Rank bottom() noexcept {
        return Rank(a1);
    }

    static constexpr Rank of(Square s) noexcept {
        return Rank(Square(s.index() & ~7));
    }

    constexpr Square first() const noexcept {
        return first_;
    }

    constexpr Square last() const noexcept {
        return Square(first().index() + 7);
    }

    constexpr BitBoard bitboard() const noexcept {
        constexpr BitBoard firstRank(0b11111111UL);
        return firstRank << first_.index();
    }

    constexpr auto squares() const noexcept {
        return util::Range<Square, Square(*)(Square)>(first_, Square(first_.index() + 7), east);
    }

    constexpr auto bitboardSquares() const noexcept {
        return util::Range<BitBoardSquare, BitBoardSquare(*)(BitBoardSquare)>(
            BitBoardSquare(first_), BitBoardSquare(first_) << 7, east);
    }

private:
    explicit constexpr Rank(Square first) : first_(first) {}

    Square first_;
};

} // namespace chess

#endif // CHESS_RANK_HPP
