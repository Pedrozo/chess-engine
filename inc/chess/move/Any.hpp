#ifndef CHESS_MOVE_ANY_HPP
#define CHESS_MOVE_ANY_HPP

#include <variant>
#include "chess/move/Regular.hpp"
#include "chess/move/Castling.hpp"
#include "chess/move/EnPassant.hpp"
#include "chess/move/Promotion.hpp"

namespace chess::move {

using Any = std::variant<Regular, Castling, EnPassant, Promotion>;

} // namespace chess::move

#endif // CHESS_MOVE_ANY_HPP
