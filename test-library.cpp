#include <iostream>

#include "chess/util/Log.hpp"
#include "chess/Attack.hpp"

int main() {
    chess::util::log(chess::queenAttack(chess::c5, chess::OccupiedBitBoard()));
    return 0;
}
