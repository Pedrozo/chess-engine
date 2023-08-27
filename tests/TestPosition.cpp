#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include "doctest.h"
#include "chess/searching/Position.hpp"
#include "chess/searching/PreComputedMove.hpp"
#include "chess/util/Log.hpp"

TEST_CASE("initial position set up") {
    chess::searching::Position position;

    for (chess::Square s : chess::Rank::of(chess::a2).squares())
        position.put(s, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));

    for (chess::Square s : chess::Rank::of(chess::a7).squares())
        position.put(s, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));

    position.put(chess::a1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::ROOK));
    position.put(chess::h1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::ROOK));

    position.put(chess::b1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::KNIGHT));
    position.put(chess::g1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::KNIGHT));

    position.put(chess::c1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::BISHOP));
    position.put(chess::f1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::BISHOP));

    position.put(chess::d1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::QUEEN));
    position.put(chess::e1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::KING));

    position.put(chess::a8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::ROOK));
    position.put(chess::h8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::ROOK));

    position.put(chess::b8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KNIGHT));
    position.put(chess::g8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KNIGHT));

    position.put(chess::c8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::BISHOP));
    position.put(chess::f8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::BISHOP));

    position.put(chess::d8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::QUEEN));
    position.put(chess::e8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KING));

    position.update();
    
    // TODO
}

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

chess::searching::PositionBitBoards firstPositionState() {
    chess::searching::PositionBitBoards expected;

    expected.players[chess::Player::WHITE].pieces[chess::Piece::PAWN] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::WHITE].pieces[chess::Piece::KNIGHT] = chess::BitBoard(0);
    expected.players[chess::Player::WHITE].pieces[chess::Piece::BISHOP] = makeBitBoard({
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::WHITE].pieces[chess::Piece::ROOK] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
    });
    expected.players[chess::Player::WHITE].pieces[chess::Piece::QUEEN] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::WHITE].pieces[chess::Piece::KING] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
    });

    expected.players[chess::Player::BLACK].pieces[chess::Piece::PAWN] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0,
        1, 0, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::BLACK].pieces[chess::Piece::KNIGHT] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::BLACK].pieces[chess::Piece::BISHOP] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::BLACK].pieces[chess::Piece::ROOK] = makeBitBoard({
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });
    expected.players[chess::Player::BLACK].pieces[chess::Piece::QUEEN] = chess::BitBoard(0);
    expected.players[chess::Player::BLACK].pieces[chess::Piece::KING] = makeBitBoard({
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });

    for (int i = 0; i < 6; i++) {
        expected.players[chess::Player::WHITE].occupied |= expected.players[chess::Player::WHITE].pieces[i];
        expected.players[chess::Player::BLACK].occupied |= expected.players[chess::Player::BLACK].pieces[i];
    }

    expected.players[chess::Player::WHITE].attack = makeBitBoard({
        0, 0, 0, 0, 0, 1, 1, 1,
        0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 1, 0, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1,
    });

    expected.players[chess::Player::BLACK].attack = makeBitBoard({
        1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 1, 0, 0, 0,
        1, 0, 1, 1, 1, 0, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 1,
        0, 1, 0, 1, 1, 0, 0, 0,
        1, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });

    expected.occupied.set(chess::d1);
    expected.occupied.set(chess::g1);
    expected.occupied.set(chess::b2);
    expected.occupied.set(chess::f2);
    expected.occupied.set(chess::g2);
    expected.occupied.set(chess::h2);
    expected.occupied.set(chess::b3);
    expected.occupied.set(chess::a4);
    expected.occupied.set(chess::c4);
    expected.occupied.set(chess::g7);
    expected.occupied.set(chess::f8);
    expected.occupied.set(chess::b4);
    expected.occupied.set(chess::a5);
    expected.occupied.set(chess::c5);
    expected.occupied.set(chess::f6);
    expected.occupied.set(chess::g6);
    expected.occupied.set(chess::b7);
    expected.occupied.set(chess::e7);
    expected.occupied.set(chess::e8);
    expected.occupied.set(chess::d7);

    return expected;
}

chess::searching::PositionBitBoards secondPositionState() {
    chess::searching::PositionBitBoards expected = firstPositionState();

    expected.occupied.reset(chess::d7);
    expected.occupied.set(chess::c8);

    expected.players[chess::Player::BLACK].occupied.reset(chess::d7);
    expected.players[chess::Player::BLACK].occupied.set(chess::c8);

    expected.players[chess::Player::BLACK].pieces[chess::Piece::KING].reset(chess::d7);
    expected.players[chess::Player::BLACK].pieces[chess::Piece::KING].set(chess::c8);

    expected.players[chess::Player::WHITE].attack = makeBitBoard({
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 1, 0, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1,
    });

    expected.players[chess::Player::BLACK].attack = makeBitBoard({
        1, 1, 1, 1, 0, 1, 1, 0,
        0, 1, 1, 1, 1, 0, 0, 0,
        1, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 1,
        0, 1, 0, 1, 1, 0, 0, 0,
        1, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });

    return expected;
}

chess::searching::PositionBitBoards thirdPositionState() {
    chess::searching::PositionBitBoards expected = secondPositionState();

    expected.occupied.reset(chess::f8);

    expected.players[chess::Player::WHITE].occupied.reset(chess::f8);
    expected.players[chess::Player::WHITE].occupied.set(chess::e7);

    expected.players[chess::Player::WHITE].pieces[chess::Piece::BISHOP].reset(chess::f8);
    expected.players[chess::Player::WHITE].pieces[chess::Piece::BISHOP].set(chess::e7);

    expected.players[chess::Player::BLACK].occupied.reset(chess::e7);
    expected.players[chess::Player::BLACK].pieces[chess::Piece::KNIGHT].reset(chess::e7);

    expected.players[chess::Player::WHITE].attack = makeBitBoard({
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 0, 0, 1, 1, 1, 0, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 1, 1, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1,
    });

    expected.players[chess::Player::BLACK].attack = makeBitBoard({
        1, 1, 1, 1, 0, 1, 1, 1,
        0, 1, 1, 1, 2, 0, 0, 0,
        1, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1,
        0, 1, 0, 1, 1, 0, 0, 0,
        1, 0, 1, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    });

    return expected;
}

TEST_CASE("einstein x oppenheimer position and final moves") {
    chess::searching::Position position;

    position.put(chess::d1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::ROOK));
    position.put(chess::g1, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::KING));
    position.put(chess::b2, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::f2, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::g2, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::h2, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::b3, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::a4, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::c4, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::PAWN));
    position.put(chess::g7, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::QUEEN));
    position.put(chess::f8, chess::PlayerPiece(chess::Player::WHITE, chess::Piece::BISHOP));

    position.put(chess::b4, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));
    position.put(chess::a5, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));
    position.put(chess::c5, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));
    position.put(chess::f6, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));
    position.put(chess::g6, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::PAWN));
    position.put(chess::b7, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::BISHOP));
    position.put(chess::e7, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KNIGHT));
    position.put(chess::e8, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::ROOK));
    position.put(chess::d7, chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KING));

    position.update();

    CHECK(position.bitboards() == firstPositionState());

    auto firstMove = chess::searching::makePreComputedMove(chess::d7, chess::c8, position);
    CHECK(firstMove.positionBitBoards == secondPositionState());

    chess::searching::ReverseMove reverseToFirst = position.apply(firstMove);
    CHECK(position.bitboards() == secondPositionState());
    CHECK(reverseToFirst.previousBitBoards == firstPositionState());
    CHECK(!reverseToFirst.captured.has_value());

    auto secondMove = chess::searching::makePreComputedMove(chess::f8, chess::e7, position);    
    CHECK(secondMove.positionBitBoards == thirdPositionState());

    chess::searching::ReverseMove reverseToSecond = position.apply(secondMove);
    CHECK(position.bitboards() == thirdPositionState());
    CHECK(reverseToSecond.previousBitBoards == secondPositionState());
    REQUIRE(reverseToSecond.captured.has_value());
    CHECK(reverseToSecond.captured.value() == chess::PlayerPiece(chess::Player::BLACK, chess::Piece::KNIGHT));

    position.apply(reverseToSecond);
    CHECK(position.bitboards() == secondPositionState());

    position.apply(reverseToFirst);
    CHECK(position.bitboards() == firstPositionState());
}
