#ifndef INCLUDED_STRATEGY_BASE_HPP
#define INCLUDED_STRATEGY_BASE_HPP 1

// Project
#include "table_t.hpp"
#include "square_pos_t.hpp"
#include "globals.hpp"

// C++
#include <vector>

namespace tictactoe {

class strategy_base {
  protected:
    // PROTECTED DATA
    const table_t &d_table;
    const std::vector<big_pos_e> &d_avail;
    int d_current_round;

  public:
    // CREATORS
    strategy_base(const table_t &table,
                  const std::vector<big_pos_e> &avail,
                  int current_round);

    virtual ~strategy_base() = default;

    // VIRTUAL METHODS
    virtual square_pos_t get_move() const = 0;

}; // class strategy_base

} // namespace tictactoe
#endif // INCLUDED_STRATEGY_BASE_HPP
