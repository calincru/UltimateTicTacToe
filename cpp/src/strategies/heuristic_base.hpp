#ifndef INCLUDED_HEURISTIC_BASE_HPP
#define INCLUDED_HEURISTIC_BASE_HPP 1

// Project
#include "table_t.hpp"
#include "player_e.hpp"
#include "square_pos_t.hpp"

// C++
#include <vector>

namespace tictactoe {

class heuristic_base {
  protected:
    const table_t &d_table;
    const std::vector<big_pos_e> &d_avail;
    player_e d_player;
    player_e d_opponent;

  public:
    // CREATORS
    heuristic_base(const table_t &table, 
                   const std::vector<big_pos_e> &avail,
                   player_e player);
    virtual ~heuristic_base() = default;

    // VIRTUAL METHODS
    virtual int evaluate() const = 0;

}; // class heuristic_base

} // namespace tictactoe
#endif // INCLUDED_HEURISTIC_BASE_HPP
