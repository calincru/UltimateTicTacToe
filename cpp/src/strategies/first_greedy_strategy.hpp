#ifndef INCLUDED_FIRST_GREEDY_STRATEGY_HPP
#define INCLUDED_FIRST_GREEDY_STRATEGY_HPP 1

// Project
#include "strategy_base.hpp"
#include "square_pos_t.hpp"

namespace tictactoe {

class first_greedy_strategy: public strategy_base {
  public:
    // CREATORS
    first_greedy_strategy(const table_t &table,
                          const std::vector<big_pos_e> &avail);

    // OVERRIDEN METHODS
    virtual square_pos_t get_move() const override;

}; // class first_greedy_strategy

} // namespace tictactoe
#endif // INCLUDED_FIRST_GREEDY_STRATEGY_HPP
