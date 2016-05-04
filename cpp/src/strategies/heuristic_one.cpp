// Self
#include "heuristic_one.hpp"

// Project
#include "square_pos_utils.hpp"
#include "utils.hpp"

#define SET_CONTAINS(set, value) (set.find(value) != set.end())

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

int heuristic_one::score_won_game(big_pos_e game,
                                  const game_types_arr &games) const {
    // FIXME
    UNUSED(game);
    UNUSED(games);

    return WON_FACTOR;
}

int heuristic_one::score_almost_won_game(big_pos_e game,
                                         const game_types_arr &games) const {
    // FIXME
    UNUSED(game);
    UNUSED(games);

    return ALMOST_WON_FACTOR;
}

int heuristic_one::score_undecided_game(big_pos_e game,
                                        const game_types_arr &games) const {
    // FIXME
    UNUSED(game);
    UNUSED(games);

    return UNDECIDED_FACTOR;
}

int heuristic_one::score_cannot_win_game(big_pos_e game,
                                         const game_types_arr &games) const {
    // FIXME
    UNUSED(game);
    UNUSED(games);

    return CANNOT_WIN_FACTOR;
}

auto heuristic_one::classify_games() const -> game_types_arr {
    auto games = game_types_arr{};

    for (auto i = 0; i < 9; ++i) {
        auto game = square_pos_utils::coord_to_big_pos(i);

        if (d_table.is_small_won_by(d_player, game)) {
            games[WON].emplace(game);
        } else if (d_table.is_small_won_by(d_opponent, game)) {
            games[LOST].emplace(game);
        } else if (d_table.count_almost_won_by(d_player, game)) {
            games[ALMOST_WON].emplace(game);
        } else if (!d_table.can_win_small(d_player, game)) {
            games[CANNOT_WIN].emplace(game);
        } else {
            games[UNDECIDED].emplace(game);
        }
    }

    return games;
}

int heuristic_one::score_games_in_line(big_pos_e game1,
                                       big_pos_e game2,
                                       big_pos_e game3,
                                       const game_types_arr &games) const {
    if (SET_CONTAINS(games[LOST], game1)
        || SET_CONTAINS(games[LOST], game2)
        || SET_CONTAINS(games[LOST], game3)) {
        return 0;
    }

    auto score_game = [&](big_pos_e game) {
        auto score = 0;

        if (SET_CONTAINS(games[WON], game)) {
            score += score_won_game(game, games);
        } else if (SET_CONTAINS(games[ALMOST_WON], game)) {
            score += score_almost_won_game(game, games);
        } else if (SET_CONTAINS(games[CANNOT_WIN], game)) {
            score += score_cannot_win_game(game, games);
        } else {
            TTT_ASSERT(SET_CONTAINS(games[UNDECIDED], game), "score invariant");
            score += score_undecided_game(game, games);
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
    auto games = classify_games();
    auto score = 0;

    for (auto i = 0; i < 3; ++i) {
        // Columns
        score += score_games_in_line(
                square_pos_utils::coord_to_big_pos(i),
                square_pos_utils::coord_to_big_pos(i + 3),
                square_pos_utils::coord_to_big_pos(i + 6),
                games
        );

        // Rows
        score += score_games_in_line(
                square_pos_utils::coord_to_big_pos(i * 3),
                square_pos_utils::coord_to_big_pos(i * 3 + 1),
                square_pos_utils::coord_to_big_pos(i * 3 + 2),
                games
        );

    }
    // Diagonals
    score += score_games_in_line(
            square_pos_utils::coord_to_big_pos(0),
            square_pos_utils::coord_to_big_pos(4),
            square_pos_utils::coord_to_big_pos(8),
            games
    );
    score += score_games_in_line(
            square_pos_utils::coord_to_big_pos(2),
            square_pos_utils::coord_to_big_pos(4),
            square_pos_utils::coord_to_big_pos(6),
            games
    );

    return score;
}

} // namespace tictactoe
