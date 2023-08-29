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
                BitBoard occupancy = BitBoard(i) << Rank::of(s).first().index();
                BitBoard result(0);

                BitBoardSquare current = s;
                while ((current & File::right().bitboard()).isEmpty()) {
                    current = east(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
                        break;
                }

                current = s;
                while ((current & File::left().bitboard()).isEmpty()) {
                    current = west(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
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
                BitBoard result(0);
                BitBoard occupancy(0);
                BitBoard flat(i);
                auto occupancyFile = File::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto fileIt = occupancyFile.begin();
                auto fileEnd = occupancyFile.end();
                auto rankIt = flatRank.begin();

                while (fileIt != fileEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupancy |= *fileIt;

                    ++fileIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & Rank::top().bitboard()).isEmpty()) {
                    current = north(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
                        break;
                }

                current = s;
                while ((current & Rank::bottom().bitboard()).isEmpty()) {
                    current = south(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
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
                BitBoard result(0);
                BitBoard occupancy(0);
                BitBoard flat(i);
                auto occupancyDiagonal = Diagonal::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto diagonalIt = occupancyDiagonal.begin();
                auto diagonalEnd = occupancyDiagonal.end();
                auto rankIt = flatRank.begin();

                while (diagonalIt != diagonalEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupancy |= *diagonalIt;

                    ++diagonalIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & (Rank::top().bitboard() | File::left().bitboard())).isEmpty()) {
                    current = northwest(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
                        break;
                }

                current = s;
                while ((current & (Rank::bottom().bitboard() | File::right().bitboard())).isEmpty()) {
                    current = southeast(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
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
                BitBoard result(0);
                BitBoard occupancy(0);
                BitBoard flat(i);
                auto occupancyAntiDiagonal = AntiDiagonal::of(s).bitboardSquares();
                auto flatRank = Rank::bottom().bitboardSquares();

                auto antidiagonalIt = occupancyAntiDiagonal.begin();
                auto antidiagonalEnd = occupancyAntiDiagonal.end();
                auto rankIt = flatRank.begin();

                while (antidiagonalIt != antidiagonalEnd) {
                    if (!(flat & (*rankIt)).isEmpty())
                        occupancy |= *antidiagonalIt;

                    ++antidiagonalIt;
                    ++rankIt;
                }

                BitBoardSquare current = s;
                while ((current & (Rank::top().bitboard() | File::right().bitboard())).isEmpty()) {
                    current = northeast(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
                        break;
                }

                current = s;
                while ((current & (Rank::bottom().bitboard() | File::left().bitboard())).isEmpty()) {
                    current = southwest(current);
                    result |= current;

                    if (!(current & occupancy).isEmpty())
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

static BitBoard rankAttack(Square s, BitBoard occupancy) noexcept {
    static ComputedRankAttacks computed;
    std::size_t i = ((occupancy >> Rank::of(s).first().index()) & Rank::bottom().bitboard()).to<std::size_t>();
    return computed.computed[s][i];
}

static BitBoard fileAttack(Square s, RotatedBitBoard<rotation::FileRotation> occupancy) noexcept {
    static ComputedFileAttacks computed;
    return computed.computed[s][occupancy.line(s)];
}

static BitBoard diagonalAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> occupancy) noexcept {
    static ComputedDiagonalAttacks computed;
    return computed.computed[s][occupancy.line(s)];
}

static BitBoard antiDiagonalAttack(Square s, RotatedBitBoard<rotation::AntiDiagonalRotation> occupancy) noexcept {
    static ComputedAntiDiagonalAttacks computed;
    return computed.computed[s][occupancy.line(s)];
}

BitBoard rookAttack(Square s, BitBoard occupancy, RotatedBitBoard<rotation::FileRotation> rotatedOccupancy) noexcept {
    return rankAttack(s, occupancy) | fileAttack(s, rotatedOccupancy);
}

BitBoard bishopAttack(Square s, RotatedBitBoard<rotation::DiagonalRotation> diagonalRotatedOccupancy,
                      RotatedBitBoard<rotation::AntiDiagonalRotation> antidiagonalRotatedOccupancy) noexcept {
    return diagonalAttack(s, diagonalRotatedOccupancy) | antiDiagonalAttack(s, antidiagonalRotatedOccupancy);
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

BitBoard queenAttack(Square s, const OccupancyBitBoard& occupancy) noexcept {
    return bishopAttack(s, occupancy.diagonalRotated(), occupancy.antiDiagonalRotated()) |
           rookAttack(s, occupancy.normal(), occupancy.fileRotated());
}

} // namespace chess
