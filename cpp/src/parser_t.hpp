#ifndef INCLUDED_PARSER_T_HPP
#define INCLUDED_PARSER_T_HPP 1

// Project
#include "boost/noncopyable.hpp"

namespace tictactoe {

// FWRD DECLS
class bot_t;

class parser_t: boost::noncopyable {
    // PRIVATE DATA
    bot_t &d_bot;

  public:
    parser_t(bot_t &bot);

    void parse_input();
}; // class parser

} // namespace tictactoe
#endif // INCLUDED_PARSER_T_HPP
