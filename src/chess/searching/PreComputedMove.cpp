#include "chess/searching/PreComputedMove.hpp"

namespace chess::searching {

PreComputedMove makePreComputedMove(Square from, Square to, const Position& position) {
    PreComputedMove move(from, to);
    PositionBitBoards& positionBitBoards = move.positionBitBoards;
    PlayerPiece movingPiece = *position.at(from);
    BitBoard fromBitBoard{BitBoardSquare(from)};
    BitBoard toBitBoard{BitBoardSquare(to)};
    BitBoard changedBits = fromBitBoard | toBitBoard;

    positionBitBoards = position.bitboards();

    positionBitBoards.occupied.reset(from);
    positionBitBoards.occupied.set(to);

    PlayerBitBoards& playerBitBoards = positionBitBoards.players[movingPiece.player()];
    playerBitBoards.occupied ^= changedBits;
    playerBitBoards.pieces[movingPiece.piece()] ^= changedBits;

    std::optional<PlayerPiece> targetSquare = position.at(to);
    if (targetSquare.has_value()) {
        PlayerBitBoards& enemyBitBoards = positionBitBoards.players[!movingPiece.player()];
        enemyBitBoards.occupied &= ~toBitBoard;
        enemyBitBoards.pieces[targetSquare->piece()] &= ~toBitBoard;
    }

    positionBitBoards.players[Player::WHITE].attack =
        attack(Player::WHITE, positionBitBoards.occupied, positionBitBoards.players[Player::WHITE].pieces);

    positionBitBoards.players[Player::BLACK].attack =
        attack(Player::BLACK, positionBitBoards.occupied, positionBitBoards.players[Player::BLACK].pieces);

    return move;
}

} // namespace chess::searching
