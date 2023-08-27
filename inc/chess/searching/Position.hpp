#ifndef CHESS_SEARCHING_POSITION_HPP
#define CHESS_SEARCHING_POSITION_HPP

#include "chess/Attack.hpp"
#include "chess/PlayerPiece.hpp"
#include "chess/Squares.hpp"
#include "chess/searching/PositionBitBoards.hpp"
#include "chess/searching/ReverseMove.hpp"
#include "chess/searching/PreComputedMove.hpp"

#include <optional>
#include <stdexcept>

namespace chess::searching {

class PreComputedMove;

class Position {
public:
    std::optional<PlayerPiece> at(Square s) const noexcept {
        return board_[s];
    }

    const PositionBitBoards& bitboards() const noexcept {
        return bitboards_;
    }

    void put(Square square, PlayerPiece playerPiece);

    ReverseMove apply(const PreComputedMove& move);

    void apply(const ReverseMove& reverseMove);

    void update();

private:
    std::optional<PlayerPiece> board_[64];
    PositionBitBoards bitboards_;
};

} // namespace chess::searching

#endif // CHESS_SEARCHING_POSITION_HPP
