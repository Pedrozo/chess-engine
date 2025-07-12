#include <array>
#include <ranges>
#include <concepts>

#include "chess/rank.hpp"
#include "chess/direction.hpp"
#include "chess/utils.hpp"
#include "chess/attack.hpp"
#include "chess/player_piece.hpp"
#include "chess/search/generate_moves.hpp"

using std::placeholders::_1;

namespace views = std::views;

namespace chess::search {

namespace {

template<typename T>
concept attack_from_square = requires (const T& t) {
  { std::invoke(t, std::declval<square>()) } -> std::convertible_to<bitboard>;
};

} // namespace

std::vector<std::pair<square, square>> generate_moves(const board::piece_centric& pieces, player turn) {
  std::vector<std::pair<square, square>> moves;

  const bitboard player_occupied = pieces.occupied_of(turn);
  const bitboard opponent_occupied = pieces.occupied_of(opponent_player(turn));

  const auto moves_generator = [&] (player_piece pp, attack_from_square auto&& attack_func, bool captures) {
    const bitboard occupied = pieces.occupied_of(pp);

    for (const bitboard from_bb : bitboard_squares(occupied)) {
      const square from(from_bb);

      bitboard attack = attack_func(from) & ~player_occupied;

      if (captures) {
        attack &= opponent_occupied;
      } else {
        attack &= ~opponent_occupied;
      }

      for (const bitboard to_bb : bitboard_squares(attack)) {
        const square to(to_bb);

        moves.emplace_back(from, to);
      }
    }
  };

  const auto pawn_fn = [&] (square s) { return pawns_attack(turn, bitboard(s), pieces.occupied()); };

  const auto bishop_fn = std::bind(bishop_attack, _1,
    pieces.rotated_occupied_45(), pieces.rotated_occupied_135());

  const auto rook_fn = std::bind(rook_attack, _1,
    pieces.occupied(), pieces.rotated_occupied_90());

  const auto queen_fn = std::bind(queen_attack, _1, pieces.occupied(),
    pieces.rotated_occupied_45(), pieces.rotated_occupied_90(), pieces.rotated_occupied_135());

  moves_generator(player_piece(turn, piece::pawn), pawn_fn, true);
  moves_generator(player_piece(turn, piece::knight), knight_attack, true);
  moves_generator(player_piece(turn, piece::bishop), bishop_fn, true);
  moves_generator(player_piece(turn, piece::rook), rook_fn, true);
  moves_generator(player_piece(turn, piece::queen), queen_fn, true);
  moves_generator(player_piece(turn, piece::king), king_attack, true);
  
  moves_generator(player_piece(turn, piece::pawn), pawn_fn, false);
  moves_generator(player_piece(turn, piece::knight), knight_attack, false);
  moves_generator(player_piece(turn, piece::bishop), bishop_fn, false);
  moves_generator(player_piece(turn, piece::rook), rook_fn, false);
  moves_generator(player_piece(turn, piece::queen), queen_fn, false);
  moves_generator(player_piece(turn, piece::king), king_attack, false);

  return moves;
}

} // namespace chess::search
