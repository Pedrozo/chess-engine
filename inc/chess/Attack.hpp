#ifndef CHESS_ATTACK_HPP
#define CHESS_ATTACK_HPP

#include <array>

#include "chess/BitBoard.hpp"
#include "chess/Square.hpp"
#include "chess/OccupancyBitBoard.hpp"
#include "chess/Player.hpp"
#include "chess/Piece.hpp"

namespace chess {

BitBoard rookAttack(Square s, BitBoard occupieod, RotatedBitBoard<rotation::FileRotation> rotatedOccupancy) noexcept;

BitBoard bishopAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> diagonalRotatedOccupancy,
                      RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotatedOccupancy) noexcept;

BitBoard knightAttack(Square s) noexcept;

BitBoard kingAttack(Square s) noexcept;

BitBoard pawnsAttack(Player player, BitBoard pawns) noexcept;

BitBoard queenAttack(Square s, const OccupancyBitBoard& occupancy) noexcept;

} // namespace chess

#endif // CHESS_ATTACK_HPP
