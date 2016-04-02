// Self
#include "minimax_one.hpp"

// Project
#include "heuristic_one.hpp"
#include "square_pos_utils.hpp"
#include "player_utils.hpp"
#include "utils.hpp"

// C++
#include <limits>

namespace tictactoe {
namespace {

// STATIC DATA
static constexpr auto INF = std::numeric_limits<int>::max();
static constexpr auto MAX_DEPTH = 1;

// STATIC FUNCTIONS
static std::pair<int, square_pos_t> negamax(table_t table,
                                            std::vector<big_pos_e> avail,
                                            player_e player,
                                            int alpha, int beta, int depth) {
    if (depth == MAX_DEPTH) {
        auto my_score = heuristic_one{table, avail, player}.evaluate();
        auto his_score
            = heuristic_one{table, avail,
                            player_utils::opponent(player)}.evaluate();

        return std::make_pair(my_score - his_score, square_pos_t{});
    }

    auto best_move = square_pos_t{};

    for (auto &game : avail) {
        for (auto &pos : table.get_avail_moves_in(game)) {
            auto move = square_pos_t{game, pos};
            auto table_cpy = table;

            table_cpy.make_owned_by(player, move);

            auto next_avail = table_cpy.get_next_available(
                                        square_pos_utils::small_to_big(pos));
            auto subtree_max = negamax(std::move(table_cpy),
                                       std::move(next_avail),
                                       player_utils::opponent(player),
                                       -beta, -alpha, depth + 1);

            if (-subtree_max.first > alpha) {
                alpha = -subtree_max.first;
                best_move = move;
            }
            if (alpha >= beta) {
                break;
            }
        }
    }

    TTT_ASSERT(alpha != -INF);
    return std::make_pair(alpha, best_move);
}

} // namespace {

minimax_one::minimax_one(const table_t &table,
                         const std::vector<big_pos_e> &avail)
    : strategy_base{table, avail} {
    // Nothing to do
}

square_pos_t minimax_one::get_move() const {
    return negamax(std::move(d_table),
                   std::move(d_avail),
                   player_e::ME,
                   -INF, INF, 0).second;
}

} // namespace tictactoe
