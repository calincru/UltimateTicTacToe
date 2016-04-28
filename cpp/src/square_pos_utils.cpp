// Self
#include "square_pos_utils.hpp"

// Project
#include "utils.hpp"

namespace tictactoe {

int square_pos_utils::pos_to_coord(small_pos_e small) {
    return static_cast<int>(small);
}

int square_pos_utils::pos_to_coord(big_pos_e big) {
    return static_cast<int>(big);
}

#ifndef DEBUG
# define DEBUG
#endif

small_pos_e square_pos_utils::coord_to_small_pos(int coord) {
    TTT_ASSERT(coord >= 0 && coord < 9, "coord_to_small_pos precondition");
    return static_cast<small_pos_e>(coord);
}

big_pos_e square_pos_utils::coord_to_big_pos(int coord) {
    TTT_ASSERT(coord >= 0 && coord < 9, "coord_to_big_pos precondition");
    return static_cast<big_pos_e>(coord);
}

square_pos_t square_pos_utils::coords_to_pos(int row, int col) {
    return {static_cast<big_pos_e>(3*(row / 3 ) + col / 3),
            static_cast<small_pos_e>(3*(row % 3) + col % 3)};
}

std::pair<int, int> square_pos_utils::pos_to_coords(const square_pos_t& pos) {
    auto big = static_cast<int>(pos.big);
    auto small = static_cast<int>(pos.small);

    return {3*(big / 3) + small / 3,
            3*(big % 3) + small % 3};
}

small_pos_e square_pos_utils::big_to_small(big_pos_e big) {
    return coord_to_small_pos(pos_to_coord(big));
}

big_pos_e square_pos_utils::small_to_big(small_pos_e small) {
    return coord_to_big_pos(pos_to_coord(small));
}

} // namespace tictactoe
