#include <array>
#include <algorithm>
#include <random>
#include "chess/ZobristHashing.hpp"

namespace chess {

struct GeneratedHashValues {

    GeneratedHashValues() : hashValue() {
        std::default_random_engine randEngine;
        randEngine.seed(666u);

        std::for_each(hashValue.begin(), hashValue.end(), [&] (auto& arr) {
            std::for_each(arr.begin(), arr.end(), [&] (std::size_t& val) {
                val = static_cast<std::size_t>(randEngine());
            });
        });
    }

    std::array<std::array<std::size_t, 12>, 64> hashValue;
};

void ZobristHashing::update(Square square, PlayerPiece playerPiece) {
    static GeneratedHashValues generatedHash;
    hash_ ^= generatedHash.hashValue[square][playerPiece];
}

} // namespace chess
