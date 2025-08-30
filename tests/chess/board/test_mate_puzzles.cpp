#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <bitset>

#include "doctest.h"

#include "chess/square.hpp"
#include "chess/bitboard.hpp"
#include "chess/rank.hpp"
#include "chess/file.hpp"
#include "chess/diagonal.hpp"
#include "chess/antidiagonal.hpp"
#include "chess/squares_iterator.hpp"
#include "chess/rotated_bitboard.hpp"
#include "chess/attack.hpp"
#include "chess/initialization.hpp"
#include "chess/bitboard_squares_iterator.hpp"
#include "chess/utils.hpp"
#include "chess/board/piece_centric.hpp"
#include "chess/search/generate_moves.hpp"
#include "chess/search/state_machine.hpp"
#include "chess/search/minimax.hpp"
#include "chess/search/alphabeta.hpp"

using namespace chess;

TEST_CASE("mate in 1") {
  initialize();

  search::state_machine board({
    {h7, black_pawn},
    {g6, black_pawn},
    {f5, black_pawn},
    {a3, black_pawn},

    {h4, white_pawn},
    {f4, white_pawn},
    {d3, white_pawn},
    {g2, white_pawn},
    {a2, white_pawn},

    {g3, white_rook},
    {b3, white_rook},

    {e1, black_queen},
  
    {h3, white_king},
    {h5, black_king},
  });

  const auto [score, best_move] = search::minimax(board, 2, player::black);

  REQUIRE(best_move);
  REQUIRE(best_move == std::make_pair(e1, h1));
}

TEST_CASE("mate in 2") {
  search::state_machine board({
    {d1, white_rook},
    {e1, white_rook},
    {g1, white_king},

    {c2, white_pawn},
    {f2, white_pawn},
    {g2, white_pawn},

    {a3, white_pawn},
    {f3, white_bishop},
    {g3, white_knight},

    {b4, white_pawn},
    {e4, white_pawn},
    {h4, white_pawn},

    {e5, black_pawn},
    {g5, white_queen},
    {h5, black_pawn},

    {c6, black_pawn},
    {d6, black_pawn},
    {g6, black_pawn},

    {a7, black_pawn},
    {b7, black_pawn},
    {c7, black_queen},
    {d7, black_knight},
    {f7, black_pawn},
    {g7, black_king},
    {h7, black_knight},

    {g8, black_rook},
    {h8, black_rook},
  });

  auto [score, best_move] = search::minimax(board, 4, player::white);

  REQUIRE(best_move);
  REQUIRE(best_move == std::make_pair(g3, f5));

  board.commit({g3, f5});
  board.commit({g7, f8});

  std::tie(score, best_move) = search::minimax(board, 2, player::white);

  REQUIRE(best_move);
  REQUIRE(best_move == std::make_pair(g5, e7));
}

TEST_CASE("another mate in 2") {
  search::state_machine board({
    {h7, black_pawn}, 
    {f7, white_queen},
    {a7, black_pawn},

    {h6, black_king},

    {f5, white_bishop},
    {e5, black_bishop},
    {d5, white_pawn},
    {c5, black_pawn},

    {c4, white_pawn},

    {h3, white_pawn},
    {b3, white_king},

    {f2, black_queen},
    {b2, white_pawn},
    {a2, white_pawn},
  });

  auto [score, best_move] = search::minimax(board, 4, player::black);

  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(f2, b2));

  board.commit({f2, b2});
  board.commit({b3, a4});

  std::tie(score, best_move) = search::minimax(board, 2, player::black);

  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(b2, b4));
}

TEST_CASE("mate in 3") {
  search::state_machine board({
    {e8, white_queen},

    {g7, black_king},
    {f7, black_pawn},

    {e6, black_pawn},

    {h5, black_pawn},
    {d5, black_pawn},

    {h4, white_king},
    {g4, black_pawn},
    {d4, white_pawn},
    {b4, white_bishop},

    {g3, white_pawn},
    {e3, white_pawn},
    {c3, white_pawn},

    {h2, white_pawn},
    {f2, white_pawn},
    {a2, white_pawn},

    {h1, black_queen},
    {a1, black_rook},
  });

  auto [score, best_move] = search::alphabeta(board, 6, player::black);

  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(h1, h2));

  board.commit({h1, h2});
  board.commit({h4, g5});
  
  std::tie(score, best_move) = search::alphabeta(board, 4, player::black);
  
  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(f7, f6));
  
  board.commit({f7, f6});
  board.commit({g5, f4});

  std::tie(score, best_move) = search::alphabeta(board, 2, player::black);

  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(h2, f2));
}

TEST_CASE("mate in 4") {
  search::state_machine board({
    {h8, black_rook},
    {f8, black_bishop},
    {e8, black_king},
    {b8, black_knight},
    {a8, black_rook},

    {g7, black_pawn},
    {e7, black_queen},
    {a7, black_pawn},

    {f5, black_pawn},
    {e5, white_knight},
    {c5, black_pawn},
    {b5, black_pawn},

    {f4, white_pawn},
    {d4, black_pawn},

    {g3, black_pawn},
    {f3, white_rook},
    {d3, white_pawn},

    {g2, white_pawn},
    {e2, white_bishop},
    {c2, white_pawn},
    {b2, white_pawn},
    {a2, white_pawn},

    {g1, white_king},
    {d1, white_queen},
    {c1, white_bishop},
    {a1, white_rook},
  });

  auto [score, best_move] = search::alphabeta(board, 8, player::black);
  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(h8, h1));

  board.commit({h8, h1});
  board.commit({g1, h1});

  std::tie(score, best_move) = search::alphabeta(board, 6, player::black);
  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(e7, h4));

  board.commit({e7, h4});
  board.commit({h1, g1});
  
  std::tie(score, best_move) = search::alphabeta(board, 4, player::black);
  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(h4, h2));
  
  board.commit({h4, h2});
  board.commit({g1, f1});
  
  std::tie(score, best_move) = search::alphabeta(board, 2, player::black);
  REQUIRE(best_move);
  REQUIRE(*best_move == std::make_pair(h2, h1));
}
