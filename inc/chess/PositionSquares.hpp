#ifndef CHESS_POSITIONSQUARES_HPP
#define CHESS_POSITIONSQUARES_HPP

#include "chess/Square.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/RegularMove.hpp"
#include "chess/CastlingMove.hpp"
#include "chess/EnPassantMove.hpp"

#include <optional>

namespace chess {

class PositionSquares {
public:
    std::optional<PlayerPiece> at(Square square) const {
        return squares_[square];
    }

    std::optional<PlayerPiece> makeMove(const RegularMove& regularMove);

    void makeMove(const CastlingMove& castlingMove);

    void makeMove(const EnPassantMove& enPassantMove);

    void unmakeMove(const RegularMove& regularMove);

    void unmakeMove(const RegularMove& regularMove, PlayerPiece capturedPiece);

    void unmakeMove(const CastlingMove& castlingMove);

    void unmakeMove(const EnPassantMove& enPassantMove);

private:
    std::optional<PlayerPiece> squares_[64];
};

} // namespace chess

#endif // CHESS_POSITIONSQUARES_HPP
