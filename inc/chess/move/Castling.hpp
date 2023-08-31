#ifndef CHESS_MOVE_CASTLING_HPP
#define CHESS_MOVE_CASTLING_HPP

#include "chess/Player.hpp"
#include "chess/Square.hpp"
#include "chess/BitBoard.hpp"

namespace chess::move {

class Castling {
public:
    enum Side {
        KING_SIDE,
        QUEEN_SIDE
    };

    constexpr Castling(Player player, Side side)
        : player_(player), side_(side) {}

    constexpr Player player() const noexcept {
        return player_;
    }

    constexpr Side side() const noexcept {
        return side_;
    }

    constexpr Square kingSquare() const noexcept {
        if (player_ == Player::WHITE)
            return e1;

        return e8;
    }

    constexpr Square targetKingSquare() const noexcept {
        if (player_ == Player::WHITE && side_ == KING_SIDE)
            return g1;

        if (player_ == Player::WHITE && side_ == QUEEN_SIDE)
            return c1;

        if (player_ == Player::BLACK && side_ == KING_SIDE)
            return g8;

        return c8;
    }

    constexpr Square rookSquare() const noexcept {
        if (player_ == Player::WHITE && side_ == KING_SIDE)
            return h1;

        if (player_ == Player::WHITE && side_ == QUEEN_SIDE)
            return a1;

        if (player_ == Player::BLACK && side_ == KING_SIDE)
            return h8;

        return a8;
    }

    constexpr Square targetRookSquare() const noexcept {
        if (player_ == Player::WHITE && side_ == KING_SIDE)
            return f1;

        if (player_ == Player::WHITE && side_ == QUEEN_SIDE)
            return d1;

        if (player_ == Player::BLACK && side_ == KING_SIDE)
            return f8;

        return d8;
    }

    constexpr BitBoard middleSquares() const noexcept {
        if (player_ == Player::WHITE && side_ == KING_SIDE)
            return BitBoard({f1, g1});

        if (player_ == Player::WHITE && side_ == QUEEN_SIDE)
            return BitBoard({b1, c1, d1});

        if (player_ == Player::BLACK && side_ == KING_SIDE)
            return BitBoard({f8, g8});

        return BitBoard({b8, c8, d8});
    }

    constexpr BitBoard kingPathSquares() const noexcept {
        if (player_ == Player::WHITE && side_ == KING_SIDE)
            return BitBoard({f1, g1});

        if (player_ == Player::WHITE && side_ == QUEEN_SIDE)
            return BitBoard({c1, d1});

        if (player_ == Player::BLACK && side_ == KING_SIDE)
            return BitBoard({f8, g8});

        return BitBoard({c8, d8});
    }

private:
    Player player_;
    Side side_;
};

} // namespace chess::move

#endif // CHESS_MOVE_CASTLING_HPP
