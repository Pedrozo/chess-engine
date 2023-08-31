#ifndef CHESS_POSITIONBITBOARDS_HPP
#define CHESS_POSITIONBITBOARDS_HPP

#include <optional>

#include "chess/Piece.hpp"
#include "chess/Player.hpp"
#include "chess/RegularMove.hpp"
#include "chess/CastlingMove.hpp"
#include "chess/EnPassantMove.hpp"
#include "chess/PromotionMove.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/OccupancyBitBoard.hpp"
#include "chess/Attack.hpp"
#include "chess/ZobristHashing.hpp"

namespace chess {

class PositionBitBoards {
public:
    explicit PositionBitBoards(std::initializer_list<std::pair<Square, PlayerPiece>> pieces);

    const OccupancyBitBoard& occupancy() const noexcept {
        return occupancy_;
    }

    BitBoard occupancy(Player player) const noexcept {
        return playerOccupancy_[player];
    }

    BitBoard attack(Player player) const noexcept {
        return playerAttack_[player];
    }

    BitBoard pieces(PlayerPiece playerPiece) const noexcept {
        return pieces_[playerPiece];
    }

    BitBoard previouslyMoved() const noexcept {
        return previouslyMoved_;
    }

    std::optional<Square> passant() const noexcept {
        return passant_;
    }

    bool isLegal(const CastlingMove& castlingMove) const noexcept;

    void makeMove(const RegularMove& regularMove, PlayerPiece movedPiece);

    void makeMove(const RegularMove& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece);

    void makeMove(const CastlingMove& castlingMove);

    void makeMove(const EnPassantMove& enPassantMove);

    void makeMove(const PromotionMove& promotionMove);

    void makeMove(const PromotionMove& promotionMove, PlayerPiece capturedPiece);

private:
    void updateAttack();

    void updateAttack(Player player);

    void addPiece(Square square, PlayerPiece piece);

    void movePiece(Square fromSquare, Square toSquare, PlayerPiece piece);

    void removePiece(Square square, PlayerPiece piece);

    void replacePiece(Square square, PlayerPiece previousPiece, PlayerPiece newPiece);

    OccupancyBitBoard occupancy_;
    BitBoard previouslyMoved_;
    BitBoard playerOccupancy_[2];
    BitBoard playerAttack_[2];
    BitBoard pieces_[12];
    std::optional<Square> passant_;
    ZobristHashing hash_;
};

} // namespace chess

#endif // CHESS_POSITIONBITBOARDS_HPP
