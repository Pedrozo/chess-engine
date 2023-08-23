#ifndef CHESS_UTIL_RANGE_HPP
#define CHESS_UTIL_RANGE_HPP

#include "Iterator.hpp"

namespace chess::util {

template<typename T, typename Next>
class Range {
public:
    constexpr Range(T first, T last, Next next = Next())
        : first_(first), last_(last), next_(std::move(next)) {}

    constexpr Iterator<T, Next> begin() const noexcept {
        return Iterator<T, Next>(first_, next_);
    }

    constexpr Iterator<T, Next> end() const noexcept {
        return Iterator<T, Next>(next_(last_), next_);
    }

private:
    T first_;
    T last_;
    Next next_;
};

} // namespace chess::util

#endif // CHESS_UTIL_RANGE_HPP
