// Self
#include "heuristic_base.hpp"

// Project
#include "player_utils.hpp"

namespace tictactoe {

heuristic_base::heuristic_base(const table_t &table, player_e player)
    : d_table{table}
    , d_player{player}
    , d_opponent{player_utils::opponent(d_player)} {
    // Nothing to do
}

} // namespace tictactoe
