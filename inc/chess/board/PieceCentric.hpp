#ifndef CHESS_BOARD_PIECECENTRIC_HPP
#define CHESS_BOARD_PIECECENTRIC_HPP

#include <array>
#include <optional>
#include <functional>

#include "chess/Piece.hpp"
#include "chess/Player.hpp"
#include "chess/move/Regular.hpp"
#include "chess/move/Castling.hpp"
#include "chess/move/EnPassant.hpp"
#include "chess/move/Promotion.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/OccupancyBitBoard.hpp"
#include "chess/Attack.hpp"
#include "chess/hash/ZobristHashing.hpp"

namespace chess::board {

class PieceCentric {
public:
    explicit PieceCentric(std::initializer_list<std::pair<Square, PlayerPiece>> pieces);

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

    bool isLegal(const move::Castling& castlingMove) const noexcept;

    void makeMove(const move::Regular& regularMove, PlayerPiece movedPiece);

    void makeMove(const move::Regular& regularMove, PlayerPiece movedPiece, PlayerPiece capturedPiece);

    void makeMove(const move::Castling& castlingMove);

    void makeMove(const move::EnPassant& enPassantMove);

    void makeMove(const move::Promotion& promotionMove);

    void makeMove(const move::Promotion& promotionMove, PlayerPiece capturedPiece);

    friend bool operator==(const PieceCentric&, const PieceCentric&);

    friend bool operator!=(const PieceCentric& board1, const PieceCentric& board2) {
        return !(board1 == board2);
    }

    friend struct std::hash<PieceCentric>;

private:
    void updateAttack();

    void updateAttack(Player player);

    void addPiece(Square square, PlayerPiece piece);

    void movePiece(Square fromSquare, Square toSquare, PlayerPiece piece);

    void removePiece(Square square, PlayerPiece piece);

    void replacePiece(Square square, PlayerPiece previousPiece, PlayerPiece newPiece);

    OccupancyBitBoard occupancy_;
    BitBoard previouslyMoved_;
    std::array<BitBoard, 2> playerOccupancy_;
    std::array<BitBoard, 2> playerAttack_;
    std::array<BitBoard, 12> pieces_;
    std::optional<Square> passant_;
    hash::ZobristHashing hash_;
};

} // namespace chess::board

namespace std {

template<>
struct hash<chess::board::PieceCentric> {
    std::size_t operator()(const chess::board::PieceCentric& board) const {
        return board.hash_.get();
    }
};

} // namespace std

#endif // CHESS_BOARD_PIECECENTRIC_HPP
