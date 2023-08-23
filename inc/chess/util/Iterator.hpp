#ifndef CHESS_UTIL_ITERATOR_HPP
#define CHESS_UTIL_ITERATOR_HPP

namespace chess::util {
    
template<typename T, typename Next>
class Iterator {
public:
    explicit constexpr Iterator(T curr, Next next = Next()) : curr_(curr), next_(std::move(next)) {}

    constexpr T operator*() const noexcept {
        return curr_;
    }

    constexpr void operator++() noexcept {
        curr_ = next_(curr_);
    }

    friend constexpr bool operator==(const Iterator& a, const Iterator& b) noexcept {
        return a.curr_ == b.curr_;
    }

    friend constexpr bool operator!=(const Iterator& a, const Iterator& b) noexcept {
        return !(a.curr_ == b.curr_);
    }

private:
    T curr_;
    Next next_;
};

} // namespace chess::util

#endif // CHESS_UTIL_ITERATOR_HPP
