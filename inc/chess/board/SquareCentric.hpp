#ifndef CHESS_BOARD_SQUARECENTRIC_HPP
#define CHESS_BOARD_SQUARECENTRIC_HPP

#include "chess/Square.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/move/Regular.hpp"
#include "chess/move/Castling.hpp"
#include "chess/move/EnPassant.hpp"
#include "chess/move/Promotion.hpp"
#include "chess/move/Backward.hpp"

#include <optional>

namespace chess::board {

class SquareCentric {
public:
    explicit SquareCentric(std::initializer_list<std::pair<Square, PlayerPiece>> pieces);

    std::optional<PlayerPiece> at(Square square) const {
        return squares_[square];
    }

    std::optional<PlayerPiece> makeMove(const move::Regular& regularMove);

    void makeMove(const move::Castling& castlingMove);

    void makeMove(const move::EnPassant& enPassantMove);

    std::optional<PlayerPiece> makeMove(const move::Promotion& promotionMove);

    void unmakeMove(const move::Backward<move::Regular>& backwardRegularMove);

    void unmakeMove(const move::Backward<move::Castling>& backwardRegularMove);

    void unmakeMove(const move::Backward<move::EnPassant>& enPassantMove);

    void unmakeMove(const move::Backward<move::Promotion>& promotionMove);

private:
    std::optional<PlayerPiece> squares_[64];
};

} // namespace chess::board

#endif // CHESS_BOARD_SQUARECENTRIC_HPP
