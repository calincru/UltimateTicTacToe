// Self
#include "heuristic_one.hpp"

// Project
#include "square_pos_utils.hpp"
#include "utils.hpp"

// C++
#include <array>

namespace tictactoe {
namespace {
    // STATIC DATA
    static constexpr auto WON_FACTOR = 10000;
    static constexpr auto ANY_MOVE_TERM = 3 * WON_FACTOR - 1;
    static constexpr auto ALMOST_WON_FACTOR = 1000;
    static constexpr auto UNDECIDED_FACTOR = 100;
    static constexpr auto CANNOT_WIN_FACTOR = 10;
} // namespace {

int heuristic_one::score_available_moves() const {
    return d_avail.size() > 1 ? ANY_MOVE_TERM : 0;
}

int heuristic_one::score_won_game(big_pos_e game) const {
    // FIXME
    UNUSED(game);

    return WON_FACTOR;
}

int heuristic_one::score_almost_won_game(big_pos_e game) const {
    // FIXME
    UNUSED(game);

    return ALMOST_WON_FACTOR;
}

int heuristic_one::score_undecided_game(big_pos_e game) const {
    // FIXME
    UNUSED(game);
    return UNDECIDED_FACTOR;
}

int heuristic_one::score_cannot_win_game(big_pos_e game) const {
    // FIXME
    UNUSED(game);

    return CANNOT_WIN_FACTOR;
}

int heuristic_one::score_games_in_line(big_pos_e game1,
                                       big_pos_e game2,
                                       big_pos_e game3) const {
    if (d_table.is_won_by(d_opponent, game1)
        || d_table.is_won_by(d_opponent, game2)
        || d_table.is_won_by(d_opponent, game3)) {
        return 0;
    }

    auto score_game = [&](big_pos_e game) {
        auto score = 0;

        if (d_table.is_won_by(d_player, game)) {
            score += score_won_game(game);
        } else if (d_table.is_almost_won_by(d_player, game)) {
            score += score_almost_won_game(game);
        } else if (!d_table.can_win(d_player, game)) {
            score += score_cannot_win_game(game);
        } else {
            score += score_undecided_game(game);
        }

        return score;
    };

    return score_available_moves()
         + score_game(game1)
         + score_game(game2)
         + score_game(game3);
}

heuristic_one::heuristic_one(const table_t &table,
                             const std::vector<big_pos_e> &avail,
                             player_e player)
    : heuristic_base{table, avail, player} {
    // Nothing to do
}

int heuristic_one::evaluate() const {
    auto score = 0;

    for (auto i = 0; i < 3; ++i) {
        // Columns
        score += score_games_in_line(
                square_pos_utils::coord_to_big_pos(i),
                square_pos_utils::coord_to_big_pos(i + 3),
                square_pos_utils::coord_to_big_pos(i + 6)
        );

        // Rows
        score += score_games_in_line(
                square_pos_utils::coord_to_big_pos(i * 3),
                square_pos_utils::coord_to_big_pos(i * 3 + 1),
                square_pos_utils::coord_to_big_pos(i * 3 + 2)
        );

    }
    // Diagonals
    score += score_games_in_line(
            square_pos_utils::coord_to_big_pos(0),
            square_pos_utils::coord_to_big_pos(4),
            square_pos_utils::coord_to_big_pos(8)
    );
    score += score_games_in_line(
            square_pos_utils::coord_to_big_pos(2),
            square_pos_utils::coord_to_big_pos(4),
            square_pos_utils::coord_to_big_pos(6)
    );

    return score;
}

} // namespace tictactoe
