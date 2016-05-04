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

    // PRIVATE FUNCTIONS
    bool check_game_won_by(player_e player) const;
    bool check_small_won_by(player_e player, big_pos_e pos) const;

  public:
    // CREATORS
    table_t();

    // ACCESSORS
    player_e get_winner() const;

    player_e get_owner_of(square_pos_t pos) const;
    int count_almost_won_by(player_e player, big_pos_e pos) const;
    bool is_small_won_by(player_e player, big_pos_e pos) const;
    bool is_small_playable(big_pos_e pos) const;
    bool can_win_small(player_e player, big_pos_e game) const;

    std::vector<small_pos_e> get_avail_moves_in(big_pos_e big) const;
    std::vector<big_pos_e> get_next_available(big_pos_e pos) const;

    // MANIPULATORS
    void make_owned_by(player_e player, square_pos_t pos);
}; // class table_t

} // namespace tictactoe
#endif // INCLUDED_TABLE_T_HPP
