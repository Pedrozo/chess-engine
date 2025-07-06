#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "chess/square.hpp"
#include "chess/bitboard.hpp"
#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/diagonal.hpp"
#include "chess/antidiagonal.hpp"
#include "chess/squares_iterator.hpp"
#include "chess/rotated_bitboard.hpp"
#include <iostream>
#include <bitset>

TEST_CASE("square") {
  CHECK(static_cast<unsigned int>(chess::square(10)) == 10);
  CHECK(static_cast<unsigned int>(chess::square(0)) == 0);
  CHECK(static_cast<unsigned int>(chess::square(63)) == 63);
  CHECK_THROWS(chess::square(64));
  CHECK_THROWS(chess::square(100));
}

