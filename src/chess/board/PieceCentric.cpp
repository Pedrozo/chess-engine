#include "chess/board/PieceCentric.hpp"

#include <algorithm>

namespace chess::board {

PieceCentric::PieceCentric(std::initializer_list<std::pair<Square, PlayerPiece>> pieces) {
    for (const auto& squarePiece : pieces)
        addPiece(squarePiece.first, squarePiece.second);

    updateAttack();
}

bool PieceCentric::isLegal(const move::Castling& castlingMove) const noexcept {
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

void PieceCentric::makeMove(const move::Regular& regularMove, PlayerPiece movedPiece) {
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

void PieceCentric::makeMove(const move::Regular& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece) {
    removePiece(regularMove.to(), capturedPiece);
    movePiece(regularMove.from(), regularMove.to(), movedPiece);
    passant_ = std::nullopt;
    updateAttack();
}

void PieceCentric::makeMove(const move::Castling& castlingMove) {
    movePiece(castlingMove.kingSquare(), castlingMove.targetKingSquare(), PlayerPiece(castlingMove.player(), Piece::KING));
    movePiece(castlingMove.rookSquare(), castlingMove.targetRookSquare(), PlayerPiece(castlingMove.player(), Piece::ROOK));
    passant_ = std::nullopt;
    updateAttack();
}

void PieceCentric::makeMove(const move::EnPassant& enPassantMove) {
    removePiece(enPassantMove.captured(), PlayerPiece(opponent(enPassantMove.player()), Piece::PAWN));
    movePiece(enPassantMove.from(), enPassantMove.to(), PlayerPiece(enPassantMove.player(), Piece::PAWN));
    passant_ = std::nullopt;
    updateAttack();
}

void PieceCentric::makeMove(const move::Promotion& promotionMove) {
    removePiece(promotionMove.from(), PlayerPiece(promotionMove.promotedPiece().player(), Piece::PAWN));
    addPiece(promotionMove.to(), promotionMove.promotedPiece());
    passant_ = std::nullopt;
    updateAttack();
}

void PieceCentric::makeMove(const move::Promotion& promotionMove, PlayerPiece capturedPiece) {
    Player player = promotionMove.promotedPiece().player();
    removePiece(promotionMove.from(), PlayerPiece(player, Piece::PAWN));
    replacePiece(promotionMove.to(), capturedPiece, promotionMove.promotedPiece());
    passant_ = std::nullopt;
    updateAttack();
}

void PieceCentric::updateAttack() {
    updateAttack(Player::WHITE);
    updateAttack(Player::BLACK);
}

void PieceCentric::updateAttack(Player player) {
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

void PieceCentric::addPiece(Square square, PlayerPiece piece) {
    BitBoardSquare pieceBitBoard(square);

    occupancy_.set(square);
    pieces_[piece] ^= pieceBitBoard;
    playerOccupancy_[piece.player()] ^= pieceBitBoard;

    hash_.update(square, piece);
}

void PieceCentric::movePiece(Square fromSquare, Square toSquare, PlayerPiece piece) {
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

void PieceCentric::removePiece(Square square, PlayerPiece piece) {
    BitBoard pieceBitBoard = BitBoardSquare(square);

    occupancy_.reset(square);
    pieces_[piece] &= ~pieceBitBoard;
    playerOccupancy_[piece.player()] &= ~pieceBitBoard;
    previouslyMoved_ |= pieceBitBoard;

    hash_.update(square, piece);
}

void PieceCentric::replacePiece(Square square, PlayerPiece previousPiece, PlayerPiece newPiece) {
    BitBoard pieceBitBoard = BitBoardSquare(square);

    pieces_[previousPiece] &= ~pieceBitBoard;
    pieces_[newPiece] |= pieceBitBoard;
    playerOccupancy_[previousPiece.player()] &= ~pieceBitBoard;
    playerOccupancy_[newPiece.player()] |= pieceBitBoard;
    previouslyMoved_ |= pieceBitBoard;

    hash_.update(square, previousPiece);
    hash_.update(square, newPiece);
}

bool operator==(const PieceCentric& board1, const PieceCentric& board2) {
    if (board1.hash_.get() != board2.hash_.get())
        return false;

    if (board1.pieces_ != board2.pieces_)
        return false;

    constexpr std::array<move::Castling, 4> castlingMoves = {
        move::Castling(Player::WHITE, move::Castling::KING_SIDE),
        move::Castling(Player::WHITE, move::Castling::QUEEN_SIDE),
        move::Castling(Player::BLACK, move::Castling::KING_SIDE),
        move::Castling(Player::BLACK, move::Castling::QUEEN_SIDE)
    };

    auto boardsHaveDiffCastlingRights = [&board1, &board2] (const move::Castling& castlingMove) {
        return board1.isLegal(castlingMove) != board2.isLegal(castlingMove);
    };

    if (std::any_of(castlingMoves.begin(), castlingMoves.end(), boardsHaveDiffCastlingRights))
        return false;

    if (board1.passant_ != board2.passant_)
        return false;

    return true;
}

} // namespace chess::board
