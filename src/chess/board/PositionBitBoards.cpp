#include "chess/board/PositionBitBoards.hpp"

namespace chess::board {

PositionBitBoards::PositionBitBoards(std::initializer_list<std::pair<Square, PlayerPiece>> pieces) {
    for (const auto& squarePiece : pieces)
        addPiece(squarePiece.first, squarePiece.second);

    updateAttack();
}

bool PositionBitBoards::isLegal(const move::Castling& castlingMove) const noexcept {
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

void PositionBitBoards::makeMove(const move::Regular& regularMove, PlayerPiece movedPiece) {
    constexpr BitBoard passantRanks[2] = {
        Rank::of(a2).bitboard() | Rank::of(a4).bitboard(),
        Rank::of(a7).bitboard() | Rank::of(a5).bitboard()
    };

    movePiece(regularMove.from(), regularMove.to(), movedPiece);
    updateAttack();

    if (movedPiece.piece() != Piece::PAWN) {
        passant_ = std::nullopt;
        return;
    }

    BitBoard moveBits = BitBoardSquare(regularMove.from()) | BitBoardSquare(regularMove.to());

    if ((moveBits & passantRanks[movedPiece.player()]) == moveBits) {
        passant_ = std::make_optional(regularMove.to());
    } else {
        passant_ = std::nullopt;
    }
}

void PositionBitBoards::makeMove(const move::Regular& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece) {
    removePiece(regularMove.to(), capturedPiece);
    movePiece(regularMove.from(), regularMove.to(), movedPiece);
    passant_ = std::nullopt;
    updateAttack();
}

void PositionBitBoards::makeMove(const move::Castling& castlingMove) {
    movePiece(castlingMove.kingSquare(), castlingMove.targetKingSquare(), PlayerPiece(castlingMove.player(), Piece::KING));
    movePiece(castlingMove.rookSquare(), castlingMove.targetRookSquare(), PlayerPiece(castlingMove.player(), Piece::ROOK));
    passant_ = std::nullopt;
    updateAttack();
}

void PositionBitBoards::makeMove(const move::EnPassant& enPassantMove) {
    removePiece(enPassantMove.captured(), PlayerPiece(opponent(enPassantMove.player()), Piece::PAWN));
    movePiece(enPassantMove.from(), enPassantMove.to(), PlayerPiece(enPassantMove.player(), Piece::PAWN));
    passant_ = std::nullopt;
    updateAttack();
}

void PositionBitBoards::makeMove(const move::Promotion& promotionMove) {
    removePiece(promotionMove.from(), PlayerPiece(promotionMove.promotedPiece().player(), Piece::PAWN));
    addPiece(promotionMove.to(), promotionMove.promotedPiece());
    passant_ = std::nullopt;
    updateAttack();
}

void PositionBitBoards::makeMove(const move::Promotion& promotionMove, PlayerPiece capturedPiece) {
    Player player = promotionMove.promotedPiece().player();
    removePiece(promotionMove.from(), PlayerPiece(player, Piece::PAWN));
    replacePiece(promotionMove.to(), capturedPiece, promotionMove.promotedPiece());
    passant_ = std::nullopt;
    updateAttack();
}

void PositionBitBoards::updateAttack() {
    updateAttack(Player::WHITE);
    updateAttack(Player::BLACK);
}

void PositionBitBoards::updateAttack(Player player) {
    auto& atk = playerAttack_[player];

    atk = BitBoard(0);

    atk |= pawnsAttack(player, pieces_[PlayerPiece(player, Piece::PAWN)]);

    for (BitBoardSquare rook : pieces_[PlayerPiece(player, Piece::ROOK)])
        atk |= rookAttack(rook.square(), occupancy_.normal(), occupancy_.fileRotated());
    
    for (BitBoardSquare bishop : pieces_[PlayerPiece(player, Piece::BISHOP)])
        atk |= bishopAttack(bishop.square(), occupancy_.diagonalRotated(), occupancy_.antiDiagonalRotated());

    for (BitBoardSquare knight : pieces_[PlayerPiece(player, Piece::KNIGHT)])
        atk |= knightAttack(knight.square());

    for (BitBoardSquare queen : pieces_[PlayerPiece(player, Piece::QUEEN)])
        atk |= queenAttack(queen.square(), occupancy_);

    for (BitBoardSquare king : pieces_[PlayerPiece(player, Piece::KING)])
        atk |= kingAttack(king.square());
}

void PositionBitBoards::addPiece(Square square, PlayerPiece piece) {
    BitBoardSquare pieceBitBoard(square);

    occupancy_.set(square);
    pieces_[piece] ^= pieceBitBoard;
    playerOccupancy_[piece.player()] ^= pieceBitBoard;

    hash_.update(square, piece);
}

void PositionBitBoards::movePiece(Square fromSquare, Square toSquare, PlayerPiece piece) {
    BitBoardSquare fromBitBoard(fromSquare);
    BitBoardSquare toBitBoard(toSquare);
    BitBoard moveBitBoard = fromBitBoard | toBitBoard;

    occupancy_.reset(fromSquare);
    occupancy_.set(toSquare);

    pieces_[piece] ^= moveBitBoard;
    playerOccupancy_[piece.player()] ^= moveBitBoard;
    previouslyMoved_ |= moveBitBoard;

    hash_.update(fromSquare, piece);
    hash_.update(toSquare, piece);
}

void PositionBitBoards::removePiece(Square square, PlayerPiece piece) {
    BitBoard pieceBitBoard = BitBoardSquare(square);

    occupancy_.reset(square);
    pieces_[piece] &= ~pieceBitBoard;
    playerOccupancy_[piece.player()] &= ~pieceBitBoard;
    previouslyMoved_ |= pieceBitBoard;

    hash_.update(square, piece);
}

void PositionBitBoards::replacePiece(Square square, PlayerPiece previousPiece, PlayerPiece newPiece) {
    BitBoard pieceBitBoard = BitBoardSquare(square);

    pieces_[previousPiece] &= ~pieceBitBoard;
    pieces_[newPiece] |= pieceBitBoard;
    playerOccupancy_[previousPiece.player()] &= ~pieceBitBoard;
    playerOccupancy_[newPiece.player()] |= pieceBitBoard;
    previouslyMoved_ |= pieceBitBoard;

    hash_.update(square, previousPiece);
    hash_.update(square, newPiece);
}

} // namespace chess::board
