#include "chess/diagonal.hpp"

namespace chess {

namespace {

inline constexpr std::array<bitboard, 64> diagonal_bitboard = {
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0000008040201008), bitboard(0x0000000080402010), bitboard(0x0000000000804020),
  bitboard(0x0000000000008040), bitboard(0x0000000000000080), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0000008040201008), bitboard(0x0000000080402010), bitboard(0x0000000000804020),
  bitboard(0x0000000000008040), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0000008040201008), bitboard(0x0000000080402010), bitboard(0x0000000000804020),
  bitboard(0x1008040201000000), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0000008040201008), bitboard(0x0000000080402010), bitboard(0x0804020100000000),
  bitboard(0x1008040201000000), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0000008040201008), bitboard(0x0402010000000000), bitboard(0x0804020100000000),
  bitboard(0x1008040201000000), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0000804020100804),
  bitboard(0x0201000000000000), bitboard(0x0402010000000000), bitboard(0x0804020100000000),
  bitboard(0x1008040201000000), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201), bitboard(0x0080402010080402), bitboard(0x0100000000000000),
  bitboard(0x0201000000000000), bitboard(0x0402010000000000), bitboard(0x0804020100000000),
  bitboard(0x1008040201000000), bitboard(0x2010080402010000), bitboard(0x4020100804020100),
  bitboard(0x8040201008040201)
};

inline constexpr std::array<square, 64> first_diagonal_square = {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, a1, b1, c1, d1, e1, f1, g1,
  a3, a2, a1, b1, c1, d1, e1, f1,
  a4, a3, a2, a1, b1, c1, d1, e1,
  a5, a4, a3, a2, a1, b1, c1, d1,
  a6, a5, a4, a3, a2, a1, b1, c1,
  a7, a6, a5, a4, a3, a2, a1, b1,
  a8, a7, a6, a5, a4, a3, a2, a1
};

inline constexpr std::array<square, 64> last_diagonal_square = {
  h8, h7, h6, h5, h4, h3, h2, h1,
  g8, h8, h7, h6, h5, h4, h3, h2,
  f8, g8, h8, h7, h6, h5, h4, h3,
  e8, f8, g8, h8, h7, h6, h5, h4,
  d8, e8, f8, g8, h8, h7, h6, h5,
  c8, d8, e8, f8, g8, h8, h7, h6,
  b8, c8, d8, e8, f8, g8, h8, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};

constexpr auto first_diagonal_square_of(square s) {
  return diagonal::iterator(int(first_diagonal_square[unsigned(s)]));
}

constexpr auto last_diagonal_square_of(square s) {
  return diagonal::iterator(int(last_diagonal_square[unsigned(s)]));
}

} // namespace

diagonal::diagonal(square s) : sq_(s) {}

diagonal::operator bitboard() const {
  return diagonal_bitboard[unsigned(sq_)];
}

diagonal::iterator diagonal::begin() const {
  return first_diagonal_square_of(sq_);
}

diagonal::iterator diagonal::end() const {
  return std::next(last_diagonal_square_of(sq_));
}

diagonal diagonal_of(square s) {
  return diagonal(s);
}

} // namespace chess
