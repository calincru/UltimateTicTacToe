// Self
#include "first_greedy_strategy.hpp"

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
    auto big = d_avail[rand() % d_avail.size()];
    auto avail = d_table.get_avail_moves_in(big);

    while (!avail.size()) {
        big = d_avail[rand() % d_avail.size()];
        avail = d_table.get_avail_moves_in(big);
    }
    auto idx = rand() % avail.size();

    return {big, avail[idx]};
}

} // namespace tictactoe
