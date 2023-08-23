#include "chess/Attack.hpp"
#include "chess/Diagonal.hpp"
#include "chess/AntiDiagonal.hpp"
#include "chess/Squares.hpp"

#include <cstdio>

namespace chess {

struct ComputedRankAttacks {
    ComputedRankAttacks() : computed() {
        for (Square s : Squares::all()) {
            for (std::size_t i = 0; i < 256; i++) {
                BitBoard occupied = BitBoard(i) << Rank::of(s).first().index();
                BitBoard result = BitBoardSquare(s);

                BitBoardSquare current = s;
                while ((current & File::right().bitboard()).isEmpty()) {
                    current = east(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                current = s;
                while ((current & File::left().bitboard()).isEmpty()) {
                    current = west(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                computed[s][i] = result;
            }
        }
    }

    BitBoard computed[64][256];
};

struct ComputedFileAttacks {
    ComputedFileAttacks() : computed() {
        for (Square s : Squares::all()) {
            for (std::size_t i = 0; i < 256; i++) {
                BitBoard result = BitBoardSquare(s);
                BitBoard occupied(0);
                BitBoard flat(i);
                auto occupiedFile = File::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto fileIt = occupiedFile.begin();
                auto fileEnd = occupiedFile.end();
                auto rankIt = flatRank.begin();

                while (fileIt != fileEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupied |= *fileIt;

                    ++fileIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & Rank::top().bitboard()).isEmpty()) {
                    current = north(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                current = s;
                while ((current & Rank::bottom().bitboard()).isEmpty()) {
                    current = south(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                computed[s][i] = result;
            }
        }
    }

    BitBoard computed[64][256];
};

struct ComputedDiagonalAttacks {
    ComputedDiagonalAttacks() : computed() {
        for (Square s : Squares::all()) {
            for (std::size_t i = 0; i < 256; i++) {
                BitBoard result = BitBoardSquare(s);
                BitBoard occupied(0);
                BitBoard flat(i);
                auto occupiedDiagonal = Diagonal::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto diagonalIt = occupiedDiagonal.begin();
                auto diagonalEnd = occupiedDiagonal.end();
                auto rankIt = flatRank.begin();

                while (diagonalIt != diagonalEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupied |= *diagonalIt;

                    ++diagonalIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & (Rank::top().bitboard() | File::left().bitboard())).isEmpty()) {
                    current = northwest(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                current = s;
                while ((current & (Rank::bottom().bitboard() | File::right().bitboard())).isEmpty()) {
                    current = southeast(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                computed[s][i] = result;
            }
        }
    }

    BitBoard computed[64][256];
};

struct ComputedAntiDiagonalAttacks {
    ComputedAntiDiagonalAttacks() : computed() {
        for (Square s : Squares::all()) {
            for (std::size_t i = 0; i < 256; i++) {
                BitBoard result = BitBoardSquare(s);
                BitBoard occupied(0);
                BitBoard flat(i);
                auto occupiedAntiDiagonal = AntiDiagonal::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto antidiagonalIt = occupiedAntiDiagonal.begin();
                auto antidiagonalEnd = occupiedAntiDiagonal.end();
                auto rankIt = flatRank.begin();

                while (antidiagonalIt != antidiagonalEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupied |= *antidiagonalIt;

                    ++antidiagonalIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & (Rank::top().bitboard() | File::right().bitboard())).isEmpty()) {
                    current = northeast(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                current = s;
                while ((current & (Rank::bottom().bitboard() | File::left().bitboard())).isEmpty()) {
                    current = southwest(current);
                    result |= current;

                    if (!(current & occupied).isEmpty())
                        break;
                }

                computed[s][i] = result;
            }
        }
    }

    BitBoard computed[64][256];
};

struct ComputedKnightAttacks {
    ComputedKnightAttacks() : computed() {
        for (Square s : Squares::all())
            computed[s] = BitBoard(0UL);

        constexpr std::array<std::pair<Square, Square>, 4> pairs = {
            std::make_pair(a1, c2), std::make_pair(a1, b3),
            std::make_pair(b1, a3), std::make_pair(c1, a2)
        };

        for (auto [a, b] : pairs) {
            bool makesSense = true;

            while (b.index() <= h8.index()) {
                if (makesSense) {
                    computed[a] |= BitBoardSquare(b);
                    computed[b] |= BitBoardSquare(a);
                }

                if (!((BitBoardSquare(a) | BitBoardSquare(b)) & File::right().bitboard()).isEmpty())
                    makesSense = !makesSense;

                a = east(a);
                b = east(b);
            }
        }
    }

    BitBoard computed[64];
};

struct ComputedKingAttacks {
    ComputedKingAttacks() : computed() {
        for (Square s : Squares::all()) {
            BitBoard result(0UL);
            BitBoardSquare bit(s);

            bool hasSouth = (bit & Rank::bottom().bitboard()).isEmpty();
            bool hasNorth = (bit & Rank::top().bitboard()).isEmpty();
            bool hasEast = (bit & File::right().bitboard()).isEmpty();
            bool hasWest = (bit & File::left().bitboard()).isEmpty();

            if (hasSouth)
                result |= south(bit);
            
            if (hasNorth)
                result |= north(bit);
            
            if (hasEast)
                result |= east(bit);
            
            if (hasWest)
                result |= west(bit);

            if (hasNorth && hasEast)
                result |= northeast(bit);

            if (hasNorth && hasWest)
                result |= northwest(bit);
            
            if (hasSouth && hasEast)
                result |= southeast(bit);
            
            if (hasSouth && hasWest)
                result |= southwest(bit);

            computed[s] = result;
        }
    }

    BitBoard computed[64];
};

static BitBoard rankAttack(Square s, BitBoard occupied) noexcept {
    static ComputedRankAttacks computed;
    std::size_t i = ((occupied >> Rank::of(s).first().index()) & Rank::bottom().bitboard()).to<std::size_t>();
    return computed.computed[s][i];
}

static BitBoard fileAttack(Square s, RotatedBitBoard<rotation::FileRotation> occupied) noexcept {
    static ComputedFileAttacks computed;
    return computed.computed[s][occupied.line(s)];
}

static BitBoard diagonalAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> occupied) noexcept {
    static ComputedDiagonalAttacks computed;
    return computed.computed[s][occupied.line(s)];
}

static BitBoard antiDiagonalAttack(Square s, RotatedBitBoard<rotation::AntiDiagonalRotation> occupied) noexcept {
    static ComputedAntiDiagonalAttacks computed;
    return computed.computed[s][occupied.line(s)];
}

BitBoard rookAttack(Square s, BitBoard occupied, RotatedBitBoard<rotation::FileRotation> rotatedOccupied) noexcept {
    return rankAttack(s, occupied) | fileAttack(s, rotatedOccupied);
}

BitBoard bishopAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> diagonalRotatedOccupied,
                      RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotatedOccupied) noexcept {
    return diagonalAttack(s, diagonalRotatedOccupied) | antiDiagonalAttack(s, antidiagonalRotatedOccupied);
}

BitBoard knightAttack(Square s) noexcept {
    static ComputedKnightAttacks computed;
    return computed.computed[s];
}

BitBoard kingAttack(Square s) noexcept {
    static ComputedKingAttacks computed;
    return computed.computed[s];
}

BitBoard pawnsAttack(Player player, BitBoard pawns) noexcept {
    BitBoard attack(0UL);

    BitBoard (*toLeft)(BitBoard) = northwest;
    BitBoard (*toRight)(BitBoard) = northeast;

    if (player == Player::BLACK) {
        toLeft = southwest;
        toRight = southeast;
    }

    attack |= toLeft((pawns & ~File::left().bitboard()));
    attack |= toRight((pawns & ~File::right().bitboard()));

    return attack;
}

BitBoard queenAttack(Square s, const OccupiedBitBoard& occupied) noexcept {
    return bishopAttack(s, occupied.diagonalRotated(), occupied.antiDiagonalRotated()) |
           rookAttack(s, occupied.normal(), occupied.fileRotated());
}

} // namespace chess
