// Self
#include "minimax_two.hpp"

// Project
#include "heuristic_two.hpp"
#include "square_pos_utils.hpp"
#include "player_utils.hpp"
#include "globals.hpp"

// C++
#include <chrono>
#include <cstdlib>

namespace tictactoe {
namespace {

// STATIC DATA
static constexpr auto STARTING_DEPTH = 4;
static constexpr auto DRAW_SCORE = 1;

// PRIVATE TYPES
struct minmax_ret_t {
    bool timeout;
    int score;
    square_pos_t move;
};
using steady_clock_tp = std::chrono::steady_clock::time_point;

// STATIC FUNCTIONS
static minmax_ret_t negamax(table_t table,
                            std::vector<big_pos_e> avail,
                            player_e player,
                            int alpha, int beta, int depth,
                            steady_clock_tp start_time, int time_limit) {
    auto opponent = player_utils::opponent(player);
    auto winner= table.get_winner();
    auto best_move = square_pos_t{};

    // Check if we still have time
    auto curr_time = std::chrono::steady_clock::now();
    auto duration_passed
            = std::chrono::duration_cast<duration_t>(curr_time - start_time);

    if (duration_passed.count() > time_limit) {
        goto timeout;
    }

    // Check if the game is won by one of the players
    if (winner != player_e::NONE) {
        if (winner == player) {
            alpha = INF;
        } else {
            alpha = -INF;
        }
        goto return_score;

    // Check if the game is a draw
    } else if (avail.size() == 0) {
        alpha = DRAW_SCORE;
        goto return_score;
    }

    // Check if we reached the maximum depth
    if (depth == 0) {
        auto my_score = heuristic_two{table, avail, player}.evaluate();
        auto opponent_avail_moves = std::vector<big_pos_e>{};
        auto his_score
            = heuristic_two{table, opponent_avail_moves, opponent}.evaluate();

        alpha = my_score - his_score;
        goto return_score;
    }

    // Recursively try all available moves
    for (auto &game : avail) {
        for (auto &pos : table.get_avail_moves_in(game)) {
            auto move = square_pos_t{game, pos};
            auto table_cpy = table;

            table_cpy.make_owned_by(player, move);

            auto next_avail = table_cpy.get_next_available(
                                        square_pos_utils::small_to_big(pos));
            auto subtree_ret = negamax(std::move(table_cpy),
                                       std::move(next_avail),
                                       opponent,
                                       -beta, -alpha, depth - 1,
                                       start_time, time_limit);

            // Check if the child timed out meanwhile
            if (subtree_ret.timeout) {
                goto timeout;
            }

            if (-subtree_ret.score > alpha) {
                alpha = -subtree_ret.score;
                best_move = move;
            }
            if (alpha >= beta) {
                goto return_score;
            }
        }
    }

return_score:
    return minmax_ret_t{false, alpha, best_move};

timeout:
    return minmax_ret_t{true, int{}, square_pos_t{}};
}

} // namespace {

///
// The time allowed is an arithemtic progression with ratio 20, which allows a
// maximum of 34 rounds.
//
// FIXME Experimenting
///
int minimax_two::get_time_limit() const {
    /* return TIME_PER_ROUND + (d_current_round - 1) * 20; */

    if (d_current_round <= 7)
        return TIME_PER_ROUND;
    if (d_current_round <= 15)
        return TIME_PER_ROUND + 250;
    if (d_current_round <= 25)
        return TIME_PER_ROUND + 500;

    return TIME_PER_ROUND + 250;
}

minimax_two::minimax_two(const table_t &table,
                         const std::vector<big_pos_e> &avail,
                         int current_round)
    : strategy_base{table, avail, current_round} {
    // Nothing to do
}

square_pos_t minimax_two::get_move() const {
    auto ret = minmax_ret_t{};
    auto best_ret = minmax_ret_t{};
    auto depth = STARTING_DEPTH;
    auto call_time = std::chrono::steady_clock::now();
    auto time_limit = get_time_limit();

    // Do IDDFS
    do {
        // Keep in @best_move the last correct move.  This is only violated by
        // the first initialization, which *must* not be the last one; check out
        // the assert below.
        best_ret = ret;

        // If we already won or lost, no need to go further
        if (ret.score == INF
            || ret.score == -INF
            || std::abs(ret.score) == DRAW_SCORE) {

            if (ret.score == INF) {
                TTT_DEBUG << "found out we will win" << std::endl;
            } else if (ret.score == -INF) {
                TTT_DEBUG << "found out we will lose" << std::endl;
            } else {
                TTT_DEBUG << "found out it will be a draw" << std::endl;
            }

            break;
        }

        // Call main minimax procedure
        ret = negamax(
            d_table,      // Game configuration
            d_avail,      // Available moves
            player_e::ME, // Player to move
            -INF - 1,     // Alpha
            INF + 1,      // Beta
            depth,        // Depth
            call_time ,   // Time of call
            time_limit    // Time limit
        );

        // Increase the depth
        ++depth;
    } while (!ret.timeout);

    // The meaning of this assert is that we *must not* get timeout on the first
    // call to the minimax procedure; aka the starting depth should be small
    // enough.
    if (ret.score != INF
        && ret.score != -INF
        && std::abs(ret.score) != DRAW_SCORE) {
        TTT_ASSERT(depth >= STARTING_DEPTH + 2, "minimax_two invariant");
    }

    TTT_DEBUG << "depth: " << depth << "; "
              << "score: " << best_ret.score
              << std::endl;

    return best_ret.move;
}

} // namespace tictactoe
