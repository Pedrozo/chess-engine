#include "chess/searching/Position.hpp"
#include <stdexcept>

namespace chess::searching {

void Position::put(Square square, PlayerPiece playerPiece) {
    if (board_[square].has_value())
            throw std::runtime_error("TODO");

    board_[square] = std::make_optional(playerPiece);

    bitboards_.occupied.set(square);

    BitBoardSquare bit(square);
    bitboards_.players[playerPiece.player()].occupied |= bit;
    bitboards_.players[playerPiece.player()].pieces[playerPiece.piece()] |= bit;
}

void Position::update() {
    bitboards_.players[Player::WHITE].attack =
        chess::attack(Player::WHITE, bitboards_.occupied, bitboards_.players[Player::WHITE].pieces);
    bitboards_.players[Player::BLACK].attack =
        chess::attack(Player::BLACK, bitboards_.occupied, bitboards_.players[Player::BLACK].pieces);
}

ReverseMove Position::apply(const PreComputedMove& move) {
    ReverseMove reverse(move.from, move.to);

    reverse.previousBitBoards = bitboards_;
    reverse.captured = board_[move.to];

    bitboards_ = move.positionBitBoards;
    board_[move.to] = board_[move.from];
    board_[move.from] = std::nullopt;

    return reverse;
}

void Position::apply(const ReverseMove& reverseMove) {
    board_[reverseMove.from] = board_[reverseMove.to];
    board_[reverseMove.to] = reverseMove.captured;
    bitboards_ = reverseMove.previousBitBoards;
}

} // namespace chess::searching
