#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "chess/search/Position.hpp"
#include "chess/util/MakeBitBoard.hpp"

using namespace chess;

TEST_CASE("regular moves") {
    search::Position pos({
        {f2, WHITE_KING},
        {h4, BLACK_KING},
        {c3, WHITE_PAWN},
        {d4, BLACK_PAWN},
        {c5, BLACK_PAWN},
        {b5, BLACK_KNIGHT}
    });

    REQUIRE(pos.squareCentric().at(f2) == WHITE_KING);
    REQUIRE(pos.squareCentric().at(h4) == BLACK_KING);
    REQUIRE(pos.squareCentric().at(c3) == WHITE_PAWN);
    REQUIRE(pos.squareCentric().at(d4) == BLACK_PAWN);
    REQUIRE(pos.squareCentric().at(c5) == BLACK_PAWN);
    REQUIRE(pos.squareCentric().at(b5) == BLACK_KNIGHT);

    REQUIRE(pos.pieceCentric().pieces(WHITE_PAWN) == BitBoard({c3}));
    REQUIRE(pos.pieceCentric().pieces(WHITE_KNIGHT).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(WHITE_ROOK).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(WHITE_BISHOP).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(WHITE_QUEEN).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(WHITE_KING) == BitBoard({f2}));

    REQUIRE(pos.pieceCentric().pieces(BLACK_PAWN) == BitBoard({d4, c5}));
    REQUIRE(pos.pieceCentric().pieces(BLACK_KNIGHT) == BitBoard({b5}));
    REQUIRE(pos.pieceCentric().pieces(BLACK_ROOK).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(BLACK_BISHOP).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(BLACK_QUEEN).isEmpty());
    REQUIRE(pos.pieceCentric().pieces(BLACK_KING) == BitBoard({h4}));

    REQUIRE(!pos.pieceCentric().passant().has_value());

    REQUIRE(pos.pieceCentric().occupancy() == OccupancyBitBoard({f2, h4, c3, d4, c5, b5}));
    REQUIRE(pos.pieceCentric().occupancy(Player::WHITE) == BitBoard({f2, c3}));
    REQUIRE(pos.pieceCentric().occupancy(Player::BLACK) == BitBoard({h4, d4, c5, b5}));

    SUBCASE("non-capture moves") {
        std::optional<PlayerPiece> captured = pos.makeMove(move::Regular(c3, c4));
        REQUIRE(!captured.has_value());
    
        captured = pos.makeMove(move::Regular(b5, c3));
        REQUIRE(!captured.has_value());

        captured = pos.makeMove(move::Regular(f2, f3));
        REQUIRE(!captured.has_value());

        REQUIRE(!pos.squareCentric().at(b5).has_value());
        REQUIRE(!pos.squareCentric().at(f2).has_value());

        REQUIRE(pos.squareCentric().at(c4).has_value());
        REQUIRE(pos.squareCentric().at(c3).has_value());
        REQUIRE(pos.squareCentric().at(f3).has_value());

        REQUIRE(pos.squareCentric().at(c4).value() == WHITE_PAWN);
        REQUIRE(pos.squareCentric().at(c3).value() == BLACK_KNIGHT);
        REQUIRE(pos.squareCentric().at(f3).value() == WHITE_KING);

        REQUIRE(pos.pieceCentric().pieces(WHITE_PAWN) == BitBoard({c4}));
        REQUIRE(pos.pieceCentric().pieces(WHITE_KING) == BitBoard({f3}));
        REQUIRE(pos.pieceCentric().pieces(BLACK_KNIGHT) == BitBoard({c3}));

        REQUIRE(pos.pieceCentric().occupancy() == OccupancyBitBoard({f3, h4, c4, d4, c5, c3}));
        REQUIRE(pos.pieceCentric().occupancy(Player::WHITE) == BitBoard({f3, c4}));
        REQUIRE(pos.pieceCentric().occupancy(Player::BLACK) == BitBoard({h4, d4, c5, c3}));

        REQUIRE(pos.pieceCentric().attack(Player::WHITE) == util::makeBitBoard({
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 1, 1, 0,
            0, 0, 0, 0, 1, 0, 1, 0,
            0, 0, 0, 0, 1, 1, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
        }));

        REQUIRE(pos.pieceCentric().attack(Player::BLACK) == util::makeBitBoard({
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 1, 0, 0, 1, 1,
            1, 1, 0, 1, 1, 0, 1, 0,
            0, 0, 1, 0, 1, 0, 1, 1,
            1, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 1, 0, 0, 0, 0,
        }));
    }

    SUBCASE("capture moves") {
        std::optional<PlayerPiece> captured = pos.makeMove(move::Regular(c3, d4));
        REQUIRE(captured.has_value());
        REQUIRE(captured.value() == BLACK_PAWN);

        captured = pos.makeMove(move::Regular(b5, d4));
        REQUIRE(captured.has_value());
        REQUIRE(captured.value() == WHITE_PAWN);

        // TODO
    }
}
