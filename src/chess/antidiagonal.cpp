#include "chess/antidiagonal.hpp"

namespace chess {

namespace {

inline constexpr std::array<bitboard, 64> antidiagonal_bitboard = {
  bitboard(0x0000000000000001), bitboard(0x0000000000000102), bitboard(0x0000000000010204),
  bitboard(0x0000000001020408), bitboard(0x0000000102040810), bitboard(0x0000010204081020),
  bitboard(0x0001020408102040), bitboard(0x0102040810204080), bitboard(0x0000000000000102),
  bitboard(0x0000000000010204), bitboard(0x0000000001020408), bitboard(0x0000000102040810),
  bitboard(0x0000010204081020), bitboard(0x0001020408102040), bitboard(0x0102040810204080),
  bitboard(0x0204081020408000), bitboard(0x0000000000010204), bitboard(0x0000000001020408),
  bitboard(0x0000000102040810), bitboard(0x0000010204081020), bitboard(0x0001020408102040),
  bitboard(0x0102040810204080), bitboard(0x0204081020408000), bitboard(0x0408102040800000),
  bitboard(0x0000000001020408), bitboard(0x0000000102040810), bitboard(0x0000010204081020),
  bitboard(0x0001020408102040), bitboard(0x0102040810204080), bitboard(0x0204081020408000),
  bitboard(0x0408102040800000), bitboard(0x0810204080000000), bitboard(0x0000000102040810),
  bitboard(0x0000010204081020), bitboard(0x0001020408102040), bitboard(0x0102040810204080),
  bitboard(0x0204081020408000), bitboard(0x0408102040800000), bitboard(0x0810204080000000),
  bitboard(0x1020408000000000), bitboard(0x0000010204081020), bitboard(0x0001020408102040),
  bitboard(0x0102040810204080), bitboard(0x0204081020408000), bitboard(0x0408102040800000),
  bitboard(0x0810204080000000), bitboard(0x1020408000000000), bitboard(0x2040800000000000),
  bitboard(0x0001020408102040), bitboard(0x0102040810204080), bitboard(0x0204081020408000),
  bitboard(0x0408102040800000), bitboard(0x0810204080000000), bitboard(0x1020408000000000),
  bitboard(0x2040800000000000), bitboard(0x4080000000000000), bitboard(0x0102040810204080),
  bitboard(0x0204081020408000), bitboard(0x0408102040800000), bitboard(0x0810204080000000),
  bitboard(0x1020408000000000), bitboard(0x2040800000000000), bitboard(0x4080000000000000),
  bitboard(0x8000000000000000)
};

inline constexpr std::array<square, 64> first_antidiagonal_square = {
  a1, b1, c1, d1, e1, f1, g1, h1,
  b1, c1, d1, e1, f1, g1, h1, h2,
  c1, d1, e1, f1, g1, h1, h2, h3,
  d1, e1, f1, g1, h1, h2, h3, h4,
  e1, f1, g1, h1, h2, h3, h4, h5,
  f1, g1, h1, h2, h3, h4, h5, h6,
  g1, h1, h2, h3, h4, h5, h6, h7,
  h1, h2, h3, h4, h5, h6, h7, h8
};

inline constexpr std::array<square, 64> last_antidiagonal_square = {
  a1, a2, a3, a4, a5, a6, a7, a8,
  a2, a3, a4, a5, a6, a7, a8, b8,
  a3, a4, a5, a6, a7, a8, b8, c8,
  a4, a5, a6, a7, a8, b8, c8, d8,
  a5, a6, a7, a8, b8, c8, d8, e8,
  a6, a7, a8, b8, c8, d8, e8, f8,
  a7, a8, b8, c8, d8, e8, f8, g8,
  a8, b8, c8, d8, e8, f8, g8, h8
};

constexpr auto first_antidiagonal_square_of(square s) {
  return antidiagonal::iterator(int(first_antidiagonal_square[unsigned(s)]));
}

constexpr auto last_antidiagonal_square_of(square s) {
  return antidiagonal::iterator(int(last_antidiagonal_square[unsigned(s)]));
}

} // namespace

antidiagonal::antidiagonal(square s) : sq_(s) {}

antidiagonal::operator bitboard() const {
  return antidiagonal_bitboard[unsigned(sq_)];
}

antidiagonal::iterator antidiagonal::begin() const {
  return first_antidiagonal_square_of(sq_);
}

antidiagonal::iterator antidiagonal::end() const {
  return std::next(last_antidiagonal_square_of(sq_));
}

antidiagonal antidiagonal_of(square s) {
  return antidiagonal(s);
}

} // namespace chess
