#include "chess/PositionBitBoards.hpp"

namespace chess {

PositionBitBoards::PositionBitBoards(std::initializer_list<std::pair<Square, PlayerPiece>> pieces) {
    for (const auto& squarePiece : pieces) {
        BitBoardSquare bit(squarePiece.first);
        occupancy_.set(squarePiece.first);
        players_[squarePiece.second.player()].occupancy.set(squarePiece.first);
        players_[squarePiece.second.player()].pieces[squarePiece.second.piece()].set(squarePiece.first);
    }

    updateAttack();
}

bool PositionBitBoards::isLegal(const CastlingMove& castlingMove) const noexcept {
    BitBoard unmoved = ~previouslyMoved_;

    BitBoardSquare kingBit = BitBoardSquare(castlingMove.kingSquare());
    BitBoardSquare rookBit = BitBoardSquare(castlingMove.rookSquare());

    if ((pieces(PlayerPiece(castlingMove.player(), Piece::KING)) & kingBit).isEmpty())
        return false;

    if ((pieces(PlayerPiece(castlingMove.player(), Piece::ROOK)) & rookBit).isEmpty())
        return false;

    if ((unmoved & kingBit).isEmpty())
        return false;

    if ((unmoved & rookBit).isEmpty())
        return false;

    if (!(occupancy(castlingMove.player()) & castlingMove.middleSquares()).isEmpty())
        return false;

    return (attack(opponent(castlingMove.player())) & (castlingMove.kingPathSquares() | kingBit)).isEmpty();
}

void PositionBitBoards::makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece) {
    BitBoard fromBit = BitBoardSquare(regularMove.from());
    BitBoard toBit = BitBoardSquare(regularMove.to());
    BitBoard movedBits = fromBit | toBit;

    occupancy_.reset(regularMove.from());
    occupancy_.set(regularMove.to());

    previouslyMoved_ |= movedBits;

    players_[movedPiece.player()].occupancy ^= movedBits;
    players_[movedPiece.player()].pieces[movedPiece.piece()] ^= movedBits;
}

void PositionBitBoards::makeMoveImpl(const RegularMove& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece) {
    makeMoveImpl(regularMove, movedPiece);
    players_[capturedPiece.player()].occupancy.reset(regularMove.to());
    players_[capturedPiece.player()].pieces[capturedPiece.piece()].reset(regularMove.to());
}

void PositionBitBoards::makeMoveImpl(const CastlingMove& castlingMove) {
    BitBoardSquare kingBit = castlingMove.kingSquare();
    BitBoardSquare rookBit = castlingMove.rookSquare();
    BitBoardSquare targetKingBit = castlingMove.targetKingSquare();
    BitBoardSquare targetRookBit = castlingMove.targetRookSquare();

    occupancy_.reset(castlingMove.kingSquare());
    occupancy_.set(castlingMove.targetKingSquare());
    occupancy_.reset(castlingMove.rookSquare());
    occupancy_.set(castlingMove.targetRookSquare());

    players_[castlingMove.player()].occupancy ^= (kingBit | rookBit | targetKingBit | targetRookBit);
    players_[castlingMove.player()].pieces[Piece::ROOK] ^= (rookBit | targetRookBit);
    players_[castlingMove.player()].pieces[Piece::KING] ^= (kingBit | targetKingBit);
}

void PositionBitBoards::updateAttack() {
    players_[Player::WHITE].attack = chess::attack(Player::WHITE, occupancy_, players_[Player::WHITE].pieces);
    players_[Player::BLACK].attack = chess::attack(Player::BLACK, occupancy_, players_[Player::BLACK].pieces);
}

} // namespace chess
