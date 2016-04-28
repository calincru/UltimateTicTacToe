#ifndef INCLUDED_BOT_T_HPP
#define INCLUDED_BOT_T_HPP 1

// Project
#include "boost/noncopyable.hpp"
#include "table_t.hpp"
#include "square_pos_t.hpp"
#include "globals.hpp"

// C++
#include <vector>

namespace tictactoe {

class bot_t: boost::noncopyable {
    // PRIVATE DATA
    int d_id;
    int d_current_round;

    table_t d_table;
    std::vector<big_pos_e> d_available;

  public:
    // MANIPULATORS
    void play();

    // Interface to the parser
    void set_timebank(int ms) { TTT_ASSERT(ms == TIMEBANK, "timebank"); }
    void set_time_per_move(int ms) { TTT_ASSERT(ms == TIME_PER_ROUND, "tpr"); }
    void set_id(int id) { d_id = id; }
    void set_current_round(int round) { d_current_round = round; }
    void update_field(std::vector<int> fields);
    void update_macroboard(std::vector<int> macroboard);
    void make_move(int time);
}; // class bot_t

} // namespace tictactoe
#endif // INCLUDED_BOT_T_HPP
