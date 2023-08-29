#ifndef CHESS_PLAYER_HPP
#define CHESS_PLAYER_HPP

namespace chess {

enum Player {
    WHITE,
    BLACK
};

inline constexpr Player opponent(Player player) {
    return static_cast<Player>(!player);
}

} // namespace chess

#endif // CHESS_PLAYER_HPP
