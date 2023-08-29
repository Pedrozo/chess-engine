#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "chess/PositionBitBoards.hpp"
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

    PositionBitBoards pos({
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

    pos.makeMove(RegularMove(f1, c4), WHITE_BISHOP, BLACK_QUEEN);

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
    PositionBitBoards pos({
        {e2, WHITE_KING},
        {h1, WHITE_ROOK},
        {a1, WHITE_ROOK},
        {e7, BLACK_KING},
        {h8, BLACK_ROOK},
        {a8, BLACK_ROOK}
    });

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)) == false);
}

TEST_CASE("castling should be illegal when the rooks haven't started at the correct positions") {
    PositionBitBoards pos({
        {e1, WHITE_KING},
        {h2, WHITE_ROOK},
        {c7, WHITE_ROOK},
        {e8, BLACK_KING},
        {d4, BLACK_ROOK},
        {a4, BLACK_ROOK}
    });

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)) == false);
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)) == false);
}

TEST_CASE("castling should be legal when the rooks and kings have started at the correct positions") {
    PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK}
    });

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be illegal when the queen is on the path or when it's attacking the opponent's path") {
    PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {d1, WHITE_QUEEN},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE))); // queen on the path
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE))); // queen attacks the path

    pos.makeMove(RegularMove(d1, g4), WHITE_QUEEN);

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE))); // queen attack the path
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE))); // queen attack the path

    pos.makeMove(RegularMove(g4, e4), WHITE_QUEEN);

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE))); // king is in check
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE))); // king is in check

    pos.makeMove(RegularMove(e4, f4), WHITE_QUEEN);
    pos.makeMove(RegularMove(f4, f1), WHITE_QUEEN);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE))); // queen on the path
    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE))); // queen attacks the path
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be iilegal when the rooks have moved") {
    PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    pos.makeMove(RegularMove(a1, a2), WHITE_ROOK);

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(a2, a1), WHITE_ROOK);

    CHECK(pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(h1, h2), WHITE_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(h2, h1), WHITE_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(a8, a7), BLACK_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(a7, a8), BLACK_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(h8, h7), BLACK_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(h7, h8), BLACK_ROOK);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));
}

TEST_CASE("castling should be illegal when the king have moved") {
    PositionBitBoards pos({
        {e1, WHITE_KING},
        {a1, WHITE_ROOK},
        {h1, WHITE_ROOK},
        {e8, BLACK_KING},
        {a8, BLACK_ROOK},
        {h8, BLACK_ROOK},
    });

    pos.makeMove(RegularMove(e1, f1), WHITE_KING);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(f1, e1), WHITE_KING);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(e8, e7), BLACK_KING);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));

    pos.makeMove(RegularMove(e7, e8), BLACK_KING);

    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::WHITE, CastlingMove::Side::QUEEN_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::KING_SIDE)));
    CHECK(!pos.isLegal(CastlingMove(Player::BLACK, CastlingMove::Side::QUEEN_SIDE)));
}

TEST_CASE("test castling") {
    PositionBitBoards pos({
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

    PositionBitBoards backup = pos;

    pos.makeMove(CastlingMove(Player::WHITE, CastlingMove::KING_SIDE));

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

    pos.makeMove(CastlingMove(Player::WHITE, CastlingMove::QUEEN_SIDE));

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

    pos.makeMove(CastlingMove(Player::BLACK, CastlingMove::KING_SIDE));

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

    pos.makeMove(CastlingMove(Player::BLACK, CastlingMove::QUEEN_SIDE));

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
