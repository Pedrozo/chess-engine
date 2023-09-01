#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "chess/board/PositionBitBoards.hpp"
#include "chess/util/Log.hpp"

using namespace chess;

chess::BitBoard makeBitBoard(const std::vector<int>& bits) {
    chess::BitBoard r(0);
    chess::BitBoardSquare b(chess::a8);

    for (int bit : bits) {
        if (bit != 0)
            r |= b;

        if ((b & chess::File::right().bitboard()).isEmpty())
            b = chess::east(b);
        else
            b = chess::south(west(b, 7));
    }

    return r;
}

TEST_CASE("queen capturing test") {

    board::PositionBitBoards pos({
        {b1, WHITE_KING},
        {d1, BLACK_KING},
        {f1, WHITE_BISHOP},
        {b2, WHITE_QUEEN},
        {d2, BLACK_ROOK},
        {h2, WHITE_PAWN},
        {f3, WHITE_PAWN},
        {g3, WHITE_PAWN},
        {c4, BLACK_QUEEN},
        {b5, BLACK_PAWN},
        {g6, BLACK_PAWN},
        {f7, BLACK_PAWN},
        {h7, BLACK_PAWN},
        {d7, WHITE_ROOK},
        {h8, BLACK_ROOK}
    });

    CHECK(pos.previouslyMoved() == BitBoard(0));

    BitBoard expectedWhiteOccupancy = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 0, 0, 1, 0, 0
    });
    CHECK(pos.occupancy(Player::WHITE) == expectedWhiteOccupancy);

    BitBoard expectedBlackOccupancy = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 1, 0, 1,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0
    });
    CHECK(pos.occupancy(Player::BLACK) == expectedBlackOccupancy);

    CHECK(pos.occupancy().normal() == (expectedWhiteOccupancy | expectedBlackOccupancy));

    CHECK(pos.pieces(WHITE_PAWN) == BitBoard({h2, f3, g3}));
    CHECK(pos.pieces(BLACK_PAWN) == BitBoard({b5, f7, g6, h7}));

    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({d7}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({d2, h8}));

    CHECK(pos.pieces(WHITE_BISHOP) == BitBoard({f1}));
    CHECK(pos.pieces(BLACK_BISHOP) == BitBoard({}));

    CHECK(pos.pieces(WHITE_KNIGHT) == BitBoard({}));
    CHECK(pos.pieces(BLACK_KNIGHT) == BitBoard({}));

    CHECK(pos.pieces(WHITE_QUEEN) == BitBoard({b2}));
    CHECK(pos.pieces(BLACK_QUEEN) == BitBoard({c4}));

    CHECK(pos.pieces(WHITE_KING) == BitBoard({b1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({d1}));

    CHECK(pos.attack(WHITE) == makeBitBoard({
        0, 0, 0, 1, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 1, 0, 0,
        0, 1, 0, 1, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 0, 1, 0,
        1, 1, 1, 0, 0, 0, 0, 0
    }));

    CHECK(pos.attack(BLACK) == makeBitBoard({
        1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 1, 0, 1, 0, 1,
        0, 0, 1, 1, 1, 0, 1, 0,
        0, 1, 1, 1, 0, 1, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 1, 1, 1, 0, 0
    }));

    pos.makeMove(move::Regular(f1, c4), WHITE_BISHOP, BLACK_QUEEN);

    expectedWhiteOccupancy ^= BitBoard({f1, c4});
    CHECK(pos.occupancy(Player::WHITE) == expectedWhiteOccupancy);

    expectedBlackOccupancy &= ~BitBoard({c4});
    CHECK(pos.occupancy(Player::BLACK) == expectedBlackOccupancy);

    CHECK(pos.pieces(WHITE_PAWN) == BitBoard({h2, f3, g3}));
    CHECK(pos.pieces(BLACK_PAWN) == BitBoard({b5, f7, g6, h7}));

    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({d7}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({d2, h8}));

    CHECK(pos.pieces(WHITE_BISHOP) == BitBoard({c4}));
    CHECK(pos.pieces(BLACK_BISHOP) == BitBoard({}));

    CHECK(pos.pieces(WHITE_KNIGHT) == BitBoard({}));
    CHECK(pos.pieces(BLACK_KNIGHT) == BitBoard({}));

    CHECK(pos.pieces(WHITE_QUEEN) == BitBoard({b2}));
    CHECK(pos.pieces(BLACK_QUEEN) == BitBoard({}));

    CHECK(pos.pieces(WHITE_KING) == BitBoard({b1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({d1}));

    CHECK(pos.attack(WHITE) == makeBitBoard({
        0, 0, 0, 1, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 1, 1, 0,
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 1, 0, 1, 1, 0, 0, 0,
        0, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 0, 0, 0,
        1, 1, 1, 0, 0, 1, 0, 0
    }));
}

TEST_CASE("castling should be illegal when the kings haven't started at the correct positions") {
    board::PositionBitBoards pos({
        {e2, WHITE_KING},
        {h1, WHITE_ROOK},
        {a1, WHITE_ROOK},
        {e7, BLACK_KING},
        {h8, BLACK_ROOK},
        {a8, BLACK_ROOK}
    });

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)) == false);
}

TEST_CASE("castling should be illegal when the rooks haven't started at the correct positions") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {h2, WHITE_ROOK},
        {c7, WHITE_ROOK},
        {e8, BLACK_KING},
        {d4, BLACK_ROOK},
        {a4, BLACK_ROOK}
    });

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)) == false);
}

TEST_CASE("castling should be legal when the rooks and kings have started at the correct positions") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK}
    });

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be illegal when the queen is on the path or when it's attacking the opponent's path") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {d1, WHITE_QUEEN},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE))); // queen on the path
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE))); // queen attacks the path

    pos.makeMove(move::Regular(d1, g4), WHITE_QUEEN);

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE))); // queen attack the path
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE))); // queen attack the path

    pos.makeMove(move::Regular(g4, e4), WHITE_QUEEN);

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE))); // king is in check
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE))); // king is in check

    pos.makeMove(move::Regular(e4, f4), WHITE_QUEEN);
    pos.makeMove(move::Regular(f4, f1), WHITE_QUEEN);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE))); // queen on the path
    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE))); // queen attacks the path
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be iilegal when the rooks have moved") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    pos.makeMove(move::Regular(a1, a2), WHITE_ROOK);

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(a2, a1), WHITE_ROOK);

    CHECK(pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(h1, h2), WHITE_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(h2, h1), WHITE_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(a8, a7), BLACK_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(a7, a8), BLACK_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(h8, h7), BLACK_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(h7, h8), BLACK_ROOK);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be illegal when the king have moved") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    pos.makeMove(move::Regular(e1, f1), WHITE_KING);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(f1, e1), WHITE_KING);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(e8, e7), BLACK_KING);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));

    pos.makeMove(move::Regular(e7, e8), BLACK_KING);

    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::WHITE, move::Castling::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::KING_SIDE)));
    CHECK(!pos.isLegal(move::Castling(Player::BLACK, move::Castling::Side::QUEEN_SIDE)));
}

TEST_CASE("test castling") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
        {a2, WHITE_PAWN},
        {b2, WHITE_PAWN},
        {c2, WHITE_PAWN},
        {d2, WHITE_PAWN},
        {e2, WHITE_PAWN},
        {f2, WHITE_PAWN},
        {g2, WHITE_PAWN},
        {h2, WHITE_PAWN},
        {a7, BLACK_PAWN},
        {b7, BLACK_PAWN},
        {c7, BLACK_PAWN},
        {d7, BLACK_PAWN},
        {e7, BLACK_PAWN},
        {f7, BLACK_PAWN},
        {g7, BLACK_PAWN},
        {h7, BLACK_PAWN},
    });

    constexpr BitBoard whitePawns = Rank::of(a2).bitboard();
    constexpr BitBoard blackPawns = Rank::of(a7).bitboard();

    board::PositionBitBoards backup = pos;

    pos.makeMove(move::Castling(Player::WHITE, move::Castling::KING_SIDE));

    CHECK(pos.occupancy().normal() == (BitBoard({g1, f1, a1, e8, a8, h8}) | whitePawns | blackPawns));
    CHECK(pos.occupancy(Player::WHITE) == (BitBoard({g1, f1, a1}) | whitePawns));
    CHECK(pos.occupancy(Player::BLACK) == (BitBoard({e8, a8, h8}) | blackPawns));
    CHECK(pos.pieces(WHITE_KING) == BitBoard({g1}));
    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({a1, f1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({e8}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({a8, h8}));
    CHECK(pos.attack(Player::WHITE) == makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1
    }));

    pos = backup;

    pos.makeMove(move::Castling(Player::WHITE, move::Castling::QUEEN_SIDE));

    CHECK(pos.occupancy().normal() == (BitBoard({c1, h1, d1, e8, a8, h8}) | whitePawns | blackPawns));
    CHECK(pos.occupancy(Player::WHITE) == (BitBoard({c1, h1, d1}) | whitePawns));
    CHECK(pos.occupancy(Player::BLACK) == (BitBoard({e8, a8, h8}) | blackPawns));
    CHECK(pos.pieces(WHITE_KING) == BitBoard({c1}));
    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({d1, h1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({e8}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({a8, h8}));
    CHECK(pos.attack(Player::WHITE) == makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 0, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 1, 1
    }));

    backup = pos;

    pos.makeMove(move::Castling(Player::BLACK, move::Castling::KING_SIDE));

    CHECK(pos.occupancy().normal() == (BitBoard({c1, h1, d1, g8, a8, f8}) | whitePawns | blackPawns));
    CHECK(pos.occupancy(Player::WHITE) == (BitBoard({c1, h1, d1}) | whitePawns));
    CHECK(pos.occupancy(Player::BLACK) == (BitBoard({g8, a8, f8}) | blackPawns));
    CHECK(pos.pieces(WHITE_KING) == BitBoard({c1}));
    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({d1, h1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({g8}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({a8, f8}));
    CHECK(pos.attack(Player::BLACK) == makeBitBoard({
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    }));

    pos = backup;

    pos.makeMove(move::Castling(Player::BLACK, move::Castling::QUEEN_SIDE));

    CHECK(pos.occupancy().normal() == (BitBoard({c1, h1, d1, c8, d8, h8}) | whitePawns | blackPawns));
    CHECK(pos.occupancy(Player::WHITE) == (BitBoard({c1, h1, d1}) | whitePawns));
    CHECK(pos.occupancy(Player::BLACK) == (BitBoard({c8, d8, h8}) | blackPawns));
    CHECK(pos.pieces(WHITE_KING) == BitBoard({c1}));
    CHECK(pos.pieces(WHITE_ROOK) == BitBoard({d1, h1}));
    CHECK(pos.pieces(BLACK_KING) == BitBoard({c8}));
    CHECK(pos.pieces(BLACK_ROOK) == BitBoard({d8, h8}));
    CHECK(pos.attack(Player::BLACK) == makeBitBoard({
        0, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    }));
}

TEST_CASE("en passant triggering cases") {
    board::PositionBitBoards pos({
        {e1, WHITE_KING},
        {e4, WHITE_PAWN},
        {h4, WHITE_PAWN},
        {b5, WHITE_PAWN},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a7, BLACK_PAWN},
        {d7, BLACK_PAWN},
        {g7, BLACK_PAWN},
    });

    pos.makeMove(move::Regular(a7, a5), BLACK_PAWN);

    board::PositionBitBoards backup = pos;

    REQUIRE(pos.passant().has_value());
    CHECK(pos.passant().value() == a5);

    pos.makeMove(move::Regular(e4, e5), WHITE_PAWN);

    CHECK(!pos.passant().has_value());

    pos = backup;

    REQUIRE(pos.passant().has_value());
    CHECK(pos.passant().value() == a5);

    pos.makeMove(move::Castling(Player::WHITE, move::Castling::KING_SIDE));

    CHECK(!pos.passant().has_value());
}

TEST_CASE("en passant captures") {
    board::PositionBitBoards pos({
        {b5, WHITE_PAWN},
        {d5, WHITE_PAWN},
        {c7, BLACK_PAWN},
        {e7, BLACK_PAWN},
        {f7, BLACK_PAWN},
    });

    board::PositionBitBoards backup = pos;

    pos.makeMove(move::Regular(c7, c5), BLACK_PAWN); 

    REQUIRE(pos.passant().has_value());
    REQUIRE(pos.passant().value() == c5);

    pos.makeMove(move::EnPassant(b5, c6));

    CHECK(!pos.passant().has_value());
    CHECK(pos.occupancy().normal() == BitBoard({d5, c6, e7, f7}));
    CHECK(pos.occupancy(Player::WHITE) == BitBoard({d5, c6}));
    CHECK(pos.occupancy(Player::BLACK) == BitBoard({e7, f7}));
    CHECK(pos.attack(Player::WHITE) == BitBoard({b7, d7, c6, e6}));
    CHECK(pos.attack(Player::BLACK) == BitBoard({d6, e6, f6, g6}));

    pos = backup;

    pos.makeMove(move::Regular(c7, c5), BLACK_PAWN); 

    REQUIRE(pos.passant().has_value());
    REQUIRE(pos.passant().value() == c5);

    pos.makeMove(move::EnPassant(d5, c6));

    CHECK(!pos.passant().has_value());
    CHECK(pos.occupancy().normal() == BitBoard({b5, c6, e7, f7}));
    CHECK(pos.occupancy(Player::WHITE) == BitBoard({b5, c6}));
    CHECK(pos.occupancy(Player::BLACK) == BitBoard({e7, f7}));
    CHECK(pos.attack(Player::WHITE) == BitBoard({b7, d7, a6, c6}));
    CHECK(pos.attack(Player::BLACK) == BitBoard({d6, e6, f6, g6}));
}
