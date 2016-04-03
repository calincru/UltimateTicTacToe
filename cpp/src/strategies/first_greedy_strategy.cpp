// Self
#include "first_greedy_strategy.hpp"

// Project
#include "player_e.hpp"
#include "square_pos_utils.hpp"
#include "utils.hpp"

// C++
#include <cstdlib>

namespace tictactoe {

first_greedy_strategy::first_greedy_strategy(
        const table_t &table,
        const std::vector<big_pos_e> &avail)
    : strategy_base{table, avail} {
    // Nothing to do
}

square_pos_t first_greedy_strategy::get_move() const {
    auto filter = [&](auto pred) {
        auto filtered = std::vector<square_pos_t>{};

        for (auto &game : d_avail) {
            for (auto &pos : d_table.get_avail_moves_in(game)) {
                auto big = square_pos_utils::small_to_big(pos);

                if (pred(big)) {
                    filtered.push_back({game, pos});
                }
            }
        }

        return filtered;
    };
    auto safest = [&](big_pos_e big) {
        return d_table.is_small_playable(big)
            && !d_table.is_small_almost_won_by(player_e::OPPONENT, big);
    };
    auto safeish = [&](big_pos_e big) {
        return d_table.is_small_playable(big);
    };
    auto dangerous = [&](big_pos_e) {
        return true;
    };

    auto safest_next = filter(safest);
    if (safest_next.size()) {
        return safest_next[std::rand() % safest_next.size()];
    }

    auto safeish_next = filter(safeish);
    if (safeish_next.size()) {
        return safeish_next[std::rand() % safeish_next.size()];
    }

    auto dangerous_next = filter(dangerous);
    return dangerous_next[std::rand() % dangerous_next.size()];
}

} // namespace tictactoe
