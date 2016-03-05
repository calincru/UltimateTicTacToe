// Self
#include "bot_t.hpp"

// Project
#include "parser_t.hpp"
#include "player_e.hpp"
#include "first_greedy_strategy.hpp"

// C++
#include <iostream>

namespace tictactoe {

void bot_t::play() {
    parser_t(*this).parse_input();
}

void bot_t::update_field(std::vector<int> fields) {
    for (auto i = 0; i < 9; ++i) {
        for (auto j = 0; j < 9; ++j) {
            auto id = fields[i * 9 + j];
            auto owner = id == 0
                            ? player_e::NONE
                            : id == d_id ? player_e::ME : player_e::OPPONENT;

            d_table.make_owned_by(owner, square_pos_t::from_coords(i, j));
        }
    }
}

void bot_t::update_macroboard(std::vector<int> macroboard) {
    d_available.clear();
    for (auto i = 0u; i < macroboard.size(); ++i) {
        if (macroboard[i] == -1) {
            d_available.emplace_back(static_cast<big_pos_e>(i));
        }
    }
}

void bot_t::make_move(int) {
    // Adjust strategy here
    auto sq_pos = first_greedy_strategy{d_table, d_available}.get_move();
    auto pos = square_pos_t::to_coords(sq_pos);

    std::cout << "place_move " << pos.second << " " << pos.first << std::endl;
}

} // namespace tictactoe
