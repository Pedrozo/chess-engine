#ifndef CHESS_ATTACK_HPP
#define CHESS_ATTACK_HPP

#include <array>

#include "chess/BitBoard.hpp"
#include "chess/Square.hpp"
#include "chess/OccupiedBitBoard.hpp"
#include "chess/Player.hpp"
#include "chess/Piece.hpp"

namespace chess {

BitBoard rookAttack(Square s, BitBoard occupieod, RotatedBitBoard<rotation::FileRotation> rotatedOccupied) noexcept;

BitBoard bishopAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> diagonalRotatedOccupied,
                      RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotatedOccupied) noexcept;

BitBoard knightAttack(Square s) noexcept;

BitBoard kingAttack(Square s) noexcept;

BitBoard pawnsAttack(Player player, BitBoard pawns) noexcept;

BitBoard queenAttack(Square s, const OccupiedBitBoard& occupied) noexcept;

template<typename PiecesMap>
BitBoard attack(Player player, const OccupiedBitBoard& occupied, const PiecesMap& pieces) noexcept {
    BitBoard result(0);

    result |= pawnsAttack(player, pieces[PAWN]);

    for (BitBoardSquare rook : pieces[ROOK])
        result |= rookAttack(rook.square(), occupied.normal(), occupied.fileRotated());

    for (BitBoardSquare bishop : pieces[BISHOP])
        result |= bishopAttack(bishop.square(), occupied.diagonalRotated(), occupied.antiDiagonalRotated());

    for (BitBoardSquare knight : pieces[KNIGHT])
        result |= knightAttack(knight.square());

    for (BitBoardSquare queen : pieces[QUEEN])
        result |= queenAttack(queen.square(), occupied);

    for (BitBoardSquare king : pieces[KING])
        result |= kingAttack(king.square());

    return result;
}

} // namespace chess

#endif // CHESS_ATTACK_HPP
