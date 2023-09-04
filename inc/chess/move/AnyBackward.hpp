#ifndef CHESS_MOVE_ANYBACKWARD_HPP
#define CHESS_MOVE_ANYBACKWARD_HPP

#include <variant>

#include "chess/move/Backward.hpp"
#include "chess/move/Any.hpp"

namespace chess::move {

using AnyBackward =std::variant<
    Backward<Regular>,
    Backward<Castling>,
    Backward<EnPassant>, 
    Backward<Promotion>>;

inline AnyBackward toBackward(const Any& move, std::optional<PlayerPiece> captured = std::nullopt) {
    // TODO: std::visit + lambda approach

    if (move.index() == 0)
        return Backward<Regular>(std::get<Regular>(move), captured);

    if (move.index() == 1)
        return Backward<Castling>(std::get<Castling>(move));

    if (move.index() == 2)
        return Backward<EnPassant>(std::get<EnPassant>(move));

    return Backward<Promotion>(std::get<Promotion>(move), captured);    
}

} // namespace chess::move

#endif // CHESS_MOVE_ANYBACKWARD_HPP
