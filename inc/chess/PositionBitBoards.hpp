#ifndef CHESS_POSITIONBITBOARDS_HPP
#define CHESS_POSITIONBITBOARDS_HPP

#include "chess/Piece.hpp"
#include "chess/Player.hpp"
#include "chess/RegularMove.hpp"
#include "chess/CastlingMove.hpp"
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

private:
    struct PlayerBitBoards {
        BitBoard pieces[6];
        BitBoard occupancy;
        BitBoard attack;
    };

    void makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece);

    void makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece);

    void makeMoveImpl(const CastlingMove& castlingMove);

    void updateAttack();

    OccupancyBitBoard occupancy_;
    BitBoard previouslyMoved_;
    PlayerBitBoards players_[2];
};

} // namespace chess

#endif // CHESS_POSITIONBITBOARDS_HPP
