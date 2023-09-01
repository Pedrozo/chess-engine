#ifndef CHESS_DIRECTION_HPP
#define CHESS_DIRECTION_HPP

#include "chess/Square.hpp"
#include "chess/BitBoardSquare.hpp"

namespace chess {

constexpr inline BitBoardSquare north(BitBoardSquare s, std::size_t count) noexcept {
    return s << (8 * count);
}

constexpr inline BitBoardSquare north(BitBoardSquare s) noexcept {
    return north(s, 1);
}

constexpr inline BitBoardSquare south(BitBoardSquare s, std::size_t count) noexcept {
    return s >> (8 * count);
}

constexpr inline BitBoardSquare south(BitBoardSquare s) noexcept {
    return south(s, 1);
}

constexpr inline BitBoardSquare east(BitBoardSquare s, std::size_t count) noexcept {
    return s << (1 * count);
}

constexpr inline BitBoardSquare east(BitBoardSquare s) noexcept {
    return east(s, 1);
}

constexpr inline BitBoardSquare west(BitBoardSquare s, std::size_t count) noexcept {
    return s >> (1 * count);
}

constexpr inline BitBoardSquare west(BitBoardSquare s) noexcept {
    return west(s, 1);
}

constexpr inline BitBoardSquare northeast(BitBoardSquare s, std::size_t count) noexcept {
    return s << (9 * count);
}

constexpr inline BitBoardSquare northeast(BitBoardSquare s) noexcept {
    return northeast(s, 1);
}

constexpr inline BitBoardSquare northwest(BitBoardSquare s, std::size_t count) noexcept {
    return s << (7 * count);
}

constexpr inline BitBoardSquare northwest(BitBoardSquare s) noexcept {
    return northwest(s, 1);
}

constexpr inline BitBoardSquare southeast(BitBoardSquare s, std::size_t count) noexcept {
    return s >> (7 * count);
}

constexpr inline BitBoardSquare southeast(BitBoardSquare s) noexcept {
    return southeast(s, 1);
}

constexpr inline BitBoardSquare southwest(BitBoardSquare s, std::size_t count) noexcept {
    return s >> (9 * count);
}

constexpr inline BitBoardSquare southwest(BitBoardSquare s) noexcept {
    return southwest(s, 1);
}

constexpr inline BitBoard north(BitBoard s, std::size_t count) noexcept {
    return s << (8 * count);
}

constexpr inline BitBoard north(BitBoard s) noexcept {
    return north(s, 1);
}

constexpr inline BitBoard south(BitBoard s, std::size_t count) noexcept {
    return s >> (8 * count);
}

constexpr inline BitBoard south(BitBoard s) noexcept {
    return south(s, 1);
}

constexpr inline BitBoard east(BitBoard s, std::size_t count) noexcept {
    return s << (1 * count);
}

constexpr inline BitBoard east(BitBoard s) noexcept {
    return east(s, 1);
}

constexpr inline BitBoard west(BitBoard s, std::size_t count) noexcept {
    return s >> (1 * count);
}

constexpr inline BitBoard west(BitBoard s) noexcept {
    return west(s, 1);
}

constexpr inline BitBoard northeast(BitBoard s, std::size_t count) noexcept {
    return s << (9 * count);
}

constexpr inline BitBoard northeast(BitBoard s) noexcept {
    return northeast(s, 1);
}

constexpr inline BitBoard northwest(BitBoard s, std::size_t count) noexcept {
    return s << (7 * count);
}

constexpr inline BitBoard northwest(BitBoard s) noexcept {
    return northwest(s, 1);
}

constexpr inline BitBoard southeast(BitBoard s, std::size_t count) noexcept {
    return s >> (7 * count);
}

constexpr inline BitBoard southeast(BitBoard s) noexcept {
    return southeast(s, 1);
}

constexpr inline BitBoard southwest(BitBoard s, std::size_t count) noexcept {
    return s >> (9 * count);
}

constexpr inline BitBoard southwest(BitBoard s) noexcept {
    return southwest(s, 1);
}

constexpr inline Square north(Square s, std::size_t count) noexcept {
    return Square(s.index() + (8 * count));
}

constexpr inline Square north(Square s) noexcept {
    return north(s, 1);
}

constexpr inline Square south(Square s, std::size_t count) noexcept {
    return Square(s.index() - (8 * count));
}

constexpr inline Square south(Square s) noexcept {
    return south(s, 1);
}

constexpr inline Square east(Square s, std::size_t count) noexcept {
    return Square(s.index() + (1 * count));
}

constexpr inline Square east(Square s) noexcept {
    return east(s, 1);
}

constexpr inline Square west(Square s, std::size_t count) noexcept {
    return Square(s.index() - (1 * count));
}

constexpr inline Square west(Square s) noexcept {
    return west(s, 1);
}

constexpr inline Square northeast(Square s, std::size_t count) noexcept {
    return Square(s.index() + (9 * count));
}

constexpr inline Square northeast(Square s) noexcept {
    return northeast(s, 1);
}

constexpr inline Square northwest(Square s, std::size_t count) noexcept {
    return Square(s.index() + (7 * count));
}

constexpr inline Square northwest(Square s) noexcept {
    return northwest(s, 1);
}

constexpr inline Square southeast(Square s, std::size_t count) noexcept {
    return Square(s.index() - (7 * count));
}

constexpr inline Square southeast(Square s) noexcept {
    return southeast(s, 1);
}

constexpr inline Square southwest(Square s, std::size_t count) noexcept {
    return Square(s.index() - (9 * count));
}

constexpr inline Square southwest(Square s) noexcept {
    return southwest(s, 1);
}

} // namespace chess

#endif // CHESS_DIRECTION_HPP
