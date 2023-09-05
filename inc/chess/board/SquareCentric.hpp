#ifndef CHESS_BOARD_SQUARECENTRIC_HPP
#define CHESS_BOARD_SQUARECENTRIC_HPP

#include "chess/Square.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/move/Regular.hpp"
#include "chess/move/Castling.hpp"
#include "chess/move/EnPassant.hpp"
#include "chess/move/Promotion.hpp"
#include "chess/move/Backward.hpp"
#include "chess/move/Any.hpp"
#include "chess/move/AnyBackward.hpp"
#include "chess/board/Visitor.hpp"

#include <optional>
#include <algorithm>

namespace chess::board {

class SquareCentric {
public:
    template<typename ForwardIt>
    SquareCentric(ForwardIt begin, ForwardIt end) : squares_() {
        std::for_each(begin, end, [&] (const std::pair<Square, PlayerPiece>& squarePiece) {
            squares_[squarePiece.first] = squarePiece.second;
        });
    }

    explicit SquareCentric(std::initializer_list<std::pair<Square, PlayerPiece>> pieces)
        : SquareCentric(pieces.begin(), pieces.end()) {}

    std::optional<PlayerPiece> at(Square square) const {
        return squares_[square];
    }

    std::optional<PlayerPiece> makeMove(const move::Regular& regularMove);

    void makeMove(const move::Castling& castlingMove);

    void makeMove(const move::EnPassant& enPassantMove);

    std::optional<PlayerPiece> makeMove(const move::Promotion& promotionMove);

    void unmakeMove(const move::Backward<move::Regular>& backwardRegularMove);

    void unmakeMove(const move::Backward<move::Castling>& backwardRegularMove);

    void unmakeMove(const move::Backward<move::EnPassant>& enPassantMove);

    void unmakeMove(const move::Backward<move::Promotion>& promotionMove);

    Visitor<SquareCentric> visitor() noexcept {
        return Visitor<SquareCentric>(*this);
    }

    Player playerInMove(const move::Regular& regularMove) const {
        return squares_[regularMove.from()]->player();
    }

    Player playerInMove(const move::Castling& castlingMove) const {
        return castlingMove.player();
    }

    Player playerInMove(const move::EnPassant& enPassantMove) const {
        return enPassantMove.player();
    }

    Player playerInMove(const move::Promotion& promotionMove) const {
        return squares_[promotionMove.from()]->player();
    }

    Player playerInMove(const move::Any& anyMove) const {
        return std::visit([&] (auto&& move) {
            return playerInMove(move);
        }, anyMove);
    }

    Player playerInMove(const move::Backward<move::Regular>& backwardRegularMove) const {
        return squares_[backwardRegularMove.move().to()]->player();
    }

    Player playerInMove(const move::Backward<move::Castling>& backwardCastlingMove) const {
        return backwardCastlingMove.move().player();
    }

    Player playerInMove(const move::Backward<move::EnPassant>& backwardEnPassantMove) const {
        return backwardEnPassantMove.move().player();
    }

    Player playerInMove(const move::Backward<move::Promotion>& backwardPromotionMove) const {
        return squares_[backwardPromotionMove.move().to()]->player();
    }

    Player playerInMove(const move::AnyBackward& anyBackwardMove) const {
        return std::visit([&] (auto&& backwardMove) {
            return playerInMove(backwardMove);
        }, anyBackwardMove);
    }

private:
    std::optional<PlayerPiece> squares_[64];
};

} // namespace chess::board

#endif // CHESS_BOARD_SQUARECENTRIC_HPP
