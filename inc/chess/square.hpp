#pragma once

#include <stdexcept>
#include <iostream>

namespace chess {

class square {
public:
  explicit constexpr square() : square_() {}

  explicit constexpr square(unsigned square) : square_(square) {
    if (square & (~0x3F)) {
      throw std::invalid_argument("invalid square");
    }
  }

  explicit constexpr operator unsigned() const { return square_; }

  explicit constexpr operator int() const { return int(square_); }

private:
  unsigned square_;
};

std::ostream& operator<<(std::ostream& os, square s);

inline constexpr square a1{ 0};
inline constexpr square b1{ 1};
inline constexpr square c1{ 2};
inline constexpr square d1{ 3};
inline constexpr square e1{ 4};
inline constexpr square f1{ 5};
inline constexpr square g1{ 6};
inline constexpr square h1{ 7};
inline constexpr square a2{ 8};
inline constexpr square b2{ 9};
inline constexpr square c2{10};
inline constexpr square d2{11};
inline constexpr square e2{12};
inline constexpr square f2{13};
inline constexpr square g2{14};
inline constexpr square h2{15};
inline constexpr square a3{16};
inline constexpr square b3{17};
inline constexpr square c3{18};
inline constexpr square d3{19};
inline constexpr square e3{20};
inline constexpr square f3{21};
inline constexpr square g3{22};
inline constexpr square h3{23};
inline constexpr square a4{24};
inline constexpr square b4{25};
inline constexpr square c4{26};
inline constexpr square d4{27};
inline constexpr square e4{28};
inline constexpr square f4{29};
inline constexpr square g4{30};
inline constexpr square h4{31};
inline constexpr square a5{32};
inline constexpr square b5{33};
inline constexpr square c5{34};
inline constexpr square d5{35};
inline constexpr square e5{36};
inline constexpr square f5{37};
inline constexpr square g5{38};
inline constexpr square h5{39};
inline constexpr square a6{40};
inline constexpr square b6{41};
inline constexpr square c6{42};
inline constexpr square d6{43};
inline constexpr square e6{44};
inline constexpr square f6{45};
inline constexpr square g6{46};
inline constexpr square h6{47};
inline constexpr square a7{48};
inline constexpr square b7{49};
inline constexpr square c7{50};
inline constexpr square d7{51};
inline constexpr square e7{52};
inline constexpr square f7{53};
inline constexpr square g7{54};
inline constexpr square h7{55};
inline constexpr square a8{56};
inline constexpr square b8{57};
inline constexpr square c8{58};
inline constexpr square d8{59};
inline constexpr square e8{60};
inline constexpr square f8{61};
inline constexpr square g8{62};
inline constexpr square h8{63};

} // namespace chess
