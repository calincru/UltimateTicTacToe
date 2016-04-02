#ifndef INCLUDED_MINIMAX_ONE_HPP
#define INCLUDED_MINIMAX_ONE_HPP 1

// Project
#include "strategy_base.hpp"
#include "square_pos_t.hpp"

namespace tictactoe {

class minimax_one: public strategy_base {
  public:
    // CREATORS
    minimax_one(const table_t &table, const std::vector<big_pos_e> &avail);

    // OVERRIDEN METHODS
    virtual square_pos_t get_move() const override;

}; // class minimax_one

} // namespace tictactoe
#endif // INCLUDED_MINIMAX_ONE_HPP
