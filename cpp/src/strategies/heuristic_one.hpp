#ifndef INCLUDED_HEURISTIC_ONE_HPP
#define INCLUDED_HEURISTIC_ONE_HPP 1

// Project
#include "heuristic_base.hpp"

namespace tictactoe {

class heuristic_one: public heuristic_base {
    // PRIVATE FUNCTIONS
    int score_available_moves() const;
    int score_won_game(big_pos_e game) const;
    int score_almost_won_game(big_pos_e game) const;
    int score_undecided_game(big_pos_e game) const;
    int score_cannot_win_game(big_pos_e game) const;
    int score_games_in_line(big_pos_e game1,
                            big_pos_e game2,
                            big_pos_e game3) const;

  public:
    // CREATORS
    heuristic_one(const table_t &table, 
                  const std::vector<big_pos_e> &avail,
                  player_e player);

    // OVERRIDEN METHODS
    virtual int evaluate() const override;

}; // class heuristic_one

} // namespace tictactoe
#endif // INCLUDED_HEURISTIC_ONE_HPP
