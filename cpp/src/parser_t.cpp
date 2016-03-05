// Project
#include "parser_t.hpp"
#include "bot_t.hpp"
#include "utils.hpp"

// C++
#include <iostream>
#include <string>
#include <sstream>

namespace tictactoe {

parser_t::parser_t(bot_t &bot)
    : d_bot{bot} {
    // Nothing to do
}

void parser_t::parse_input() {
    auto line = std::string{};

    while (std::getline(std::cin, line)) {
        std::istringstream iss{line};
        auto str = std::string{};

        iss >> str;
        if (str == "settings") {
            auto what = std::string{};
            int which;

            iss >> what >> which;
            if (what == "timebank") {
                d_bot.set_timebank(which);
            } else if (what == "time_per_move") {
                d_bot.set_time_per_move(which);
            } else if (what == "your_botid") {
                d_bot.set_id(which);
            }

            // Ignore anything else for now
        } else if (str == "update") {
            // Discard "game" token
            iss >> str;

            auto what = std::string{};
            iss >> what;

            if (what == "round") {
                int round;

                iss >> round;
                d_bot.set_current_round(round);
            } else if (what == "field") {
                auto fields_str = std::string{};
                iss >> fields_str;

                auto split = utils::comma_split(fields_str);
                auto fields = std::vector<int>{};

                for (auto &f : split) {
                    fields.emplace_back(std::stoi(f));
                }

                d_bot.update_field(std::move(fields));
            } else if (what == "macroboard") {
                auto macroboard_str = std::string{};
                iss >> macroboard_str;

                auto split = utils::comma_split(macroboard_str);
                auto macroboard = std::vector<int>{};

                for (auto &m : split) {
                    macroboard.emplace_back(std::stoi(m));
                }

                d_bot.update_macroboard(std::move(macroboard));
            }
        } else if (str == "action") {
            auto what = std::string{};
            int time;

            iss >> what >> time;
            TTT_ASSERT(what == "move");

            d_bot.make_move(time);
        }
    }
}

} // namespace tictactoe
