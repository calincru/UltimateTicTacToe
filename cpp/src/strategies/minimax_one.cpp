// Self
#include "minimax_one.hpp"

// Project
#include "heuristic_one.hpp"
#include "square_pos_utils.hpp"
#include "player_utils.hpp"

namespace tictactoe {
namespace {

// STATIC DATA
static constexpr auto INF = 0x3f3f3f3f;
static constexpr auto MAX_DEPTH = 2;

// STATIC FUNCTIONS
static std::pair<int, square_pos_t> negamax(table_t table,
                                            std::vector<big_pos_e> avail,
                                            player_e player,
                                            int alpha, int beta, int depth) {
    auto opponent = player_utils::opponent(player);
    auto finished = table.is_finished();
    auto best_move = square_pos_t{};

    if (finished.first) {
        if (finished.second == player) {
            alpha = INF;
        } else if (finished.second == opponent) {
            alpha = -INF;
        } else {
            alpha = 0;
        }

        goto _exit;
    }

    if (depth == MAX_DEPTH) {
        auto my_score = heuristic_one{table, avail, player}.evaluate();
        auto opponent_avail_moves = std::vector<big_pos_e>{};
        auto his_score
            = heuristic_one{table, opponent_avail_moves, opponent}.evaluate();

        alpha = my_score - his_score;
        goto _exit;
    }

    for (auto &game : avail) {
        for (auto &pos : table.get_avail_moves_in(game)) {
            auto move = square_pos_t{game, pos};
            auto table_cpy = table;

            table_cpy.make_owned_by(player, move);

            auto next_avail = table_cpy.get_next_available(
                                        square_pos_utils::small_to_big(pos));
            auto subtree_max = negamax(std::move(table_cpy),
                                       std::move(next_avail),
                                       opponent,
                                       -beta, -alpha, depth + 1);

            if (alpha == -INF || -subtree_max.first > alpha) {
                alpha = -subtree_max.first;
                best_move = move;
            }
            if (alpha >= beta) {
                goto _exit;
            }
        }
    }

_exit:
    return std::make_pair(alpha, best_move);
}

} // namespace {

minimax_one::minimax_one(const table_t &table,
                         const std::vector<big_pos_e> &avail)
    : strategy_base{table, avail} {
    // Nothing to do
}

square_pos_t minimax_one::get_move() const {
    return negamax(d_table, d_avail, player_e::ME, -INF, INF, 0).second;
}

} // namespace tictactoe
