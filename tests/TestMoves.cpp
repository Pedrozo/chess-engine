#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "PositionBitBoards.hpp"
#include "PositionSquares.hpp"

using namespace chess;

TEST_CASE("simple moves with no captures") {
    PositionSquares posSquares({
        {e2, WHITE_KING},
        {b4, WHITE_ROOK},
        {e6, BLACK_QUEEN},
        {f3, BLACK_PAWN}
    });

    PositionBitBoards posBitboards({
        {e2, WHITE_KING},
        {b4, WHITE_ROOK},
        {e6, BLACK_QUEEN},
        {f3, BLACK_PAWN}
    });

    // TODO: test initial position

    move::Regular move1(e2, d3);

    auto captured = posSquares.makeMove(move1);
}
