#include "chess/square.hpp"

namespace chess {

std::ostream& operator<<(std::ostream& os, square s) {
  char str[3];
  str[0] = 'a' + unsigned(s) % 8;
  str[1] = '1' + unsigned(s) / 8;
  str[2] = '\0';
  os << str;
  return os;
}

} // namespace chess
