// Self
#include "player_utils.hpp"

// Project
#include "utils.hpp"

namespace tictactoe {

player_e player_utils::opponent(player_e player) {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT);
    return player == player_e::OPPONENT ? player_e::ME
                                        : player_e::OPPONENT;
}

} // namespace tictactoe
