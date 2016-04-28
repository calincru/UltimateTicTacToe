// Self
#include "strategy_base.hpp"

namespace tictactoe {

strategy_base::strategy_base(const table_t &table,
                             const std::vector<big_pos_e> &avail,
                             int current_round)
    : d_table{table}
    , d_avail{avail}
    , d_current_round{current_round} {
    // Nothing to do
}

} // namespace tictactoe
