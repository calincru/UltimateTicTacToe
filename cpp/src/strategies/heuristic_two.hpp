#ifndef INCLUDED_HEURISTIC_TWO_HPP
#define INCLUDED_HEURISTIC_TWO_HPP 1

// Project
#include "heuristic_base.hpp"
#include "table_t.hpp"
#include "square_pos_t.hpp"
#include "player_e.hpp"

// C++
#include <array>
#include <unordered_map>

namespace tictactoe {

class heuristic_two: public heuristic_base {
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
    int score_available_moves() const;
    int score_won_game(big_pos_e game) const;
    int score_almost_won_game(big_pos_e game) const;
    int score_undecided_game(big_pos_e game) const;

    int score_and_classify_games(game_types_arr &games) const;
    int score_games_in_line(big_pos_e game1,
                            big_pos_e game2,
                            big_pos_e game3,
                            const game_types_arr &games) const;

  public:
    // CREATORS
    heuristic_two(const table_t &table, player_e player);

    // OVERRIDEN METHODS
    virtual int evaluate() const override;

}; // class heuristic_two

} // namespace tictactoe
#endif // INCLUDED_HEURISTIC_TWO_HPP
