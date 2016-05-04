#ifndef INCLUDED_HEURISTIC_ONE_HPP
#define INCLUDED_HEURISTIC_ONE_HPP 1

// Project
#include "heuristic_base.hpp"
#include "table_t.hpp"
#include "square_pos_t.hpp"
#include "player_e.hpp"

// C++
#include <array>

namespace tictactoe {

class heuristic_one: public heuristic_base {
    // PRIVATE TYPES
    enum small_game_states {
        WON,
        ALMOST_WON,
        UNDECIDED,
        CANNOT_WIN,
        LOST
    };
    using game_types_arr = std::array<table_t::big_pos_set_t, 5>;

    // PRIVATE FUNCTIONS
    int score_won_game(big_pos_e game, const game_types_arr &games) const;
    int score_almost_won_game(big_pos_e game, const game_types_arr &gms) const;
    int score_undecided_game(big_pos_e game, const game_types_arr &gms) const;
    int score_cannot_win_game(big_pos_e game, const game_types_arr &gms) const;

    game_types_arr classify_games() const;
    int score_games_in_line(big_pos_e game1,
                            big_pos_e game2,
                            big_pos_e game3,
                            const game_types_arr &games) const;

  public:
    // CREATORS
    heuristic_one(const table_t &table, player_e player);

    // OVERRIDEN METHODS
    virtual int evaluate() const override;

}; // class heuristic_one

} // namespace tictactoe
#endif // INCLUDED_HEURISTIC_ONE_HPP
