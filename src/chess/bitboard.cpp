#include "chess/bitboard.hpp"

namespace chess {

std::ostream& operator<<(std::ostream& os, bitboard board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char c = bool(bitboard(board) & bitboard(1UL << ((56 - i * 8) + j))) ? '1' : '0';
      os << c << " ";
    }

    os << "\n";
  }

  return os;
}

} // namespace chess
