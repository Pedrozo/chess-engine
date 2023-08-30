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

namespace chess {

class PositionBitBoards {
public:
    explicit PositionBitBoards(std::initializer_list<std::pair<Square, PlayerPiece>> pieces);

    const OccupancyBitBoard& occupancy() const noexcept {
        return occupancy_;
    }

    BitBoard occupancy(Player player) const noexcept {
        return players_[player].occupancy;
    }

    BitBoard attack(Player player) const noexcept {
        return players_[player].attack;
    }

    BitBoard pieces(PlayerPiece playerPiece) const noexcept {
        return players_[playerPiece.player()].pieces[playerPiece.piece()];
    }

    BitBoard previouslyMoved() const noexcept {
        return previouslyMoved_;
    }

    std::optional<Square> passant() const noexcept {
        return passant_;
    }

    bool isLegal(const CastlingMove& castlingMove) const noexcept;

    void makeMove(const RegularMove& regularMove, PlayerPiece movedPiece) {
        makeMoveImpl(regularMove, movedPiece);
        updateAttack();
    }

    void makeMove(const RegularMove& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece) {
        makeMoveImpl(regularMove, movedPiece, capturedPiece);
        updateAttack();
    }

    void makeMove(const CastlingMove& castlingMove) {
        makeMoveImpl(castlingMove);
        updateAttack();
    }

    void makeMove(const EnPassantMove& enPassantMove) {
        makeMoveImpl(enPassantMove);
        updateAttack();
    }

    void makeMove(const PromotionMove& promotionMove) {
        makeMoveImpl(promotionMove);
        updateAttack();
    }

    void makeMove(const PromotionMove& promotionMove, PlayerPiece capturedPiece) {
        makeMoveImpl(promotionMove, capturedPiece);
        updateAttack();
    }

private:
    struct PlayerBitBoards {
        BitBoard pieces[6];
        BitBoard occupancy;
        BitBoard attack;
    };

    void makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece);

    void makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece);

    void makeMoveImpl(const CastlingMove& castlingMove);

    void makeMoveImpl(const EnPassantMove& enPassantMove);

    void makeMoveImpl(const PromotionMove& promotionMove);

    void makeMoveImpl(const PromotionMove& promotionMove, PlayerPiece capturedPiece);

    void updateAttack();

    OccupancyBitBoard occupancy_;
    BitBoard previouslyMoved_;
    PlayerBitBoards players_[2];
    std::optional<Square> passant_;
};

} // namespace chess

#endif // CHESS_POSITIONBITBOARDS_HPP
