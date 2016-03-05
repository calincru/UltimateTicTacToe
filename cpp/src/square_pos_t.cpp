// Self
#include "square_pos_t.hpp"

// Project
#include "square_pos_utils.hpp"

namespace tictactoe {

std::size_t small_pos_hash_t::operator()(small_pos_e pos) const {
    return square_pos_utils::pos_to_coord(pos);
}

std::size_t big_pos_hash_t::operator()(big_pos_e pos) const {
    return square_pos_utils::pos_to_coord(pos);
}

std::size_t square_pos_hash_t::operator()(const square_pos_t &pos) const {
    auto coords = square_pos_utils::pos_to_coords(pos);

    return std::hash<int>{}(coords.first * 9 + coords.second);
}

} // namespace tictactoe
