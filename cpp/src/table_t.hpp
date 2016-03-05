#ifndef INCLUDED_TABLE_T_HPP
#define INCLUDED_TABLE_T_HPP 1

// Project
#include "player_e.hpp"
#include "square_pos_t.hpp"

// C++
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace tictactoe {

class table_t {
  public:
    // PUBLIC TYPES
    using big_pos_set_t = std::unordered_set<big_pos_e, big_pos_hash_t>;

  private:
    // PRIVATE TYPES
    using board_t = std::unordered_map<square_pos_t,
                                       player_e,
                                       square_pos_hash_t>;

    // PRIVATE DATA
    board_t d_board;
    big_pos_set_t d_mines;
    big_pos_set_t d_his;
    big_pos_set_t d_draws;

    // PRIVATE FUNCTIONS
    bool check_owned_by(player_e player, big_pos_e pos) const;
    bool check_draw(big_pos_e pos) const;

  public:
    // CREATORS
    table_t();

    // ACCESSORS
    player_e get_owner_of(square_pos_t pos) const;
    bool is_won_by(player_e player, big_pos_e pos) const;
    bool is_draw(big_pos_e pos) const;
    big_pos_set_t get_games_own_by(player_e player) const;
    big_pos_set_t get_draws() const;
    std::vector<small_pos_e> get_avail_moves_in(big_pos_e big) const;

    // MANIPULATORS
    void make_owned_by(player_e player, square_pos_t pos);
}; // class table_t

} // namespace tictactoe
#endif // INCLUDED_TABLE_T_HPP