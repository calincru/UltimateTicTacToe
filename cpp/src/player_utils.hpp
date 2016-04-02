#ifndef INCLUDED_PLAYER_UTILS_HPP
#define INCLUDED_PLAYER_UTILS_HPP 1

// Project
#include "player_e.hpp"

namespace tictactoe {

struct player_utils {
    static player_e opponent(player_e player);
};

} // namespace tictactoe
#endif // INCLUDED_PLAYER_UTILS_HPP
