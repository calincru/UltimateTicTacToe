#ifndef INCLUDED_SQUARE_POS_UTILS_HPP
#define INCLUDED_SQUARE_POS_UTILS_HPP 1

// Project
#include "square_pos_t.hpp"

// C++
#include <utility>

namespace tictactoe {

struct square_pos_utils {
    static int pos_to_coord(small_pos_e small);
    static int pos_to_coord(big_pos_e big);

    static small_pos_e coord_to_small_pos(int coord);
    static big_pos_e coord_to_big_pos(int coord);

    static square_pos_t coords_to_pos(int row, int col);
    static std::pair<int, int> pos_to_coords(const square_pos_t& pos);

    static small_pos_e big_to_small(big_pos_e big);
    static big_pos_e small_to_big(small_pos_e small);
}; // struct square_pos_utils

} // namespace tictactoe
#endif // INCLUDED_SQUARE_POS_UTILS_HPP
