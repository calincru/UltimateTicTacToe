#ifndef INCLUDED_MINIMAX_TWO_HPP
#define INCLUDED_MINIMAX_TWO_HPP 1

// Project
#include "strategy_base.hpp"
#include "square_pos_t.hpp"

namespace tictactoe {

class minimax_two: public strategy_base {
    // PRIVATE FUNCTIONS
    int get_time_limit() const;

  public:
    // CREATORS
    minimax_two(const table_t &table,
                const std::vector<big_pos_e> &avail,
                int current_round);

    // OVERRIDEN METHODS
    virtual square_pos_t get_move() const override;

}; // class minimax_two

} // namespace tictactoe
#endif // INCLUDED_MINIMAX_TWO_HPP
