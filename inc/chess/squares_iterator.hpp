#pragma once

#include "square.hpp"
#include <iterator>

namespace chess {

template<int I>
class squares_iterator {
public:
  using value_type = square;
  using difference_type = int;

  static inline constexpr int skip_count = I;

  constexpr squares_iterator() = default;

  explicit constexpr squares_iterator(int val) : val_(val) {}

  constexpr square operator*() const { return square(val_); }

  constexpr squares_iterator& operator++() { val_ += skip_count; return *this; }

  constexpr squares_iterator& operator--() { val_ -= skip_count; return *this; }

  constexpr squares_iterator operator++(int) { squares_iterator tmp = *this; ++(*this); return tmp; }

  constexpr squares_iterator operator--(int) { squares_iterator tmp = *this; --(*this); return tmp; }

  constexpr squares_iterator& operator+=(int count) { val_ += skip_count * count; return *this; }

  constexpr squares_iterator& operator-=(int count) { val_ -= skip_count * count; return *this; }

  constexpr value_type operator[](int i) const { return square(val_ + skip_count * i); }

  friend constexpr difference_type operator-(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ - rhs.val_; }

  friend constexpr squares_iterator operator+(squares_iterator iter, int n) { return squares_iterator(iter.val_ + skip_count * n); }

  friend constexpr squares_iterator operator+(int n, squares_iterator iter) { return squares_iterator(iter.val_ + skip_count * n); }

  friend constexpr squares_iterator operator-(squares_iterator iter, int n) { return squares_iterator(iter.val_ - skip_count * n); }

  friend constexpr squares_iterator operator-(int n, squares_iterator iter) { return squares_iterator(iter.val_ - skip_count * n); }

  friend constexpr bool operator==(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ == rhs.val_; }

  friend constexpr bool operator!=(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ != rhs.val_; }

  friend constexpr bool operator<(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ < rhs.val_; }
  
  friend constexpr bool operator>(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ > rhs.val_; }

  friend constexpr bool operator<=(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ <= rhs.val_; }
  
  friend constexpr bool operator>=(squares_iterator lhs, squares_iterator rhs) { return lhs.val_ >= rhs.val_; }

private:
  int val_;
};

} // namespace chess
