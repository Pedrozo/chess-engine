#ifndef CHESS_ZOBRISTHASHING_HPP
#define CHESS_ZOBRISTHASHING_HPP

#include <cstdint>
#include "chess/Square.hpp"
#include "chess/PlayerPiece.hpp"

namespace chess {

class ZobristHashing {
public:
    ZobristHashing() : hash_(0) {}

    std::size_t get() const noexcept {
        return hash_;
    }

    void update(Square square, PlayerPiece playerPiece);

private:
    std::size_t hash_;
};

} // namespace chess

#endif // CHESS_ZOBRISTHASHING_HPP
