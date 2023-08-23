#ifndef CHESS_ATTACK_HPP
#define CHESS_ATTACK_HPP

#include <array>

#include "chess/BitBoard.hpp"
#include "chess/Square.hpp"
#include "chess/OccupiedBitBoard.hpp"
#include "chess/Player.hpp"

namespace chess {

BitBoard rookAttack(Square s, BitBoard occupieod, RotatedBitBoard<rotation::FileRotation> rotatedOccupied) noexcept;

BitBoard bishopAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> diagonalRotatedOccupied,
                      RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotatedOccupied) noexcept;

BitBoard knightAttack(Square s) noexcept;

BitBoard kingAttack(Square s) noexcept;

BitBoard pawnsAttack(Player player, BitBoard pawns) noexcept;

BitBoard queenAttack(Square s, const OccupiedBitBoard& occupied) noexcept;

} // namespace chess

#endif // CHESS_ATTACK_HPP
