#ifndef CHESS_MOVE_BACKWARD_HPP
#define CHESS_MOVE_BACKWARD_HPP

#include <optional>

namespace chess::move {

template<typename T, bool moveMayCapture = T::mayCapture>
class Backward {};

template<typename T>
class Backward<T, false> {
public:
    explicit Backward(T move)
        : move_(std::move(move)) {}

    const T& move() const noexcept {
        return move_;
    }

private:
    T move_;
};

template<typename T>
class Backward<T, true> {
public:
    explicit Backward(T move, std::optional<PlayerPiece> captured = std::nullopt)
        : move_(std::move(move)), captured_(captured) {}

    const T& move() const noexcept {
        return move_;
    }

    std::optional<PlayerPiece> captured() const noexcept {
        return captured_;
    }

private:
    T move_;
    std::optional<PlayerPiece> captured_;
};

} // namespace chess::move

#endif // CHESS_MOVE_BACKWARD_HPP
