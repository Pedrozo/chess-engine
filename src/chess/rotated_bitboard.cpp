#include <array>

#include "chess/rotated_bitboard.hpp"
#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/diagonal.hpp"
#include "chess/antidiagonal.hpp"
#include "chess/squares_iterator.hpp"

namespace chess {

namespace {

std::array<unsigned, 64> shift_45;
std::array<square, 64> rotated_45;

std::array<unsigned, 64> shift_90;
std::array<square, 64> rotated_90;

std::array<unsigned, 64> shift_135;
std::array<square, 64> rotated_135;

void initialize_45() {
  static constexpr std::array<square, 15> starts = {
    a1, b1, c1, d1, e1, f1, g1, h1, a2, a3, a4, a5, a6, a7, a8
  };

  squares_iterator<1> rot(0);

  for (const square st : starts) {
    const unsigned shift(*rot);

    for (const square c : diagonal_of(st)) {
      shift_45[unsigned(c)] = shift;
      rotated_45[unsigned(c)] = *rot++;
    }
  }
}

void initialize_135() {
  static constexpr std::array<square, 15> starts = {
    a1, b1, c1, d1, e1, f1, g1, h1, h2, h3, h4, h5, h6, h7, h8
  };

  squares_iterator<1> rot(0);

  for (const square st : starts) {
    const unsigned shift(*rot);

    for (const square c : antidiagonal_of(st)) {
      shift_135[unsigned(c)] = shift;
      rotated_135[unsigned(c)] = *rot++;
    }
  }
}

void initialize_90() {
  constexpr unsigned offset(*file(0).begin());

  for (unsigned i = 0; i < 64; i++) {
    rotated_90[i] = square(((i & 7) << 3) | (i >> 3));
    shift_90[i] = (unsigned(*file_of(square(i)).begin()) - offset) << 3;
  }
}

} // namespace

void initialize_rotated_boards() {
  initialize_45();
  initialize_90();
  initialize_135();
}

square rotate_45_fn::operator()(square s) const {
  return rotated_45[unsigned(s)];
}

square rotate_90_fn::operator()(square s) const {
  return rotated_90[unsigned(s)];
}

square rotate_135_fn::operator()(square s) const {
  return rotated_135[unsigned(s)];
}

bitboard align_rank(square s, bitboard bb) {
  return bb >>= unsigned(*rank_of(s).begin());
}

bitboard align_file(square s, rotated_bitboard_90 bb) {
  return bitboard(bb) >> shift_90[unsigned(s)];
}

bitboard align_diagonal(square s, rotated_bitboard_45 bb) {  
  return bitboard(bb) >> shift_45[unsigned(s)];
}

bitboard align_antidiagonal(square s, rotated_bitboard_135 bb) {
  return bitboard(bb) >> shift_135[unsigned(s)];
}

} // namespace chess
