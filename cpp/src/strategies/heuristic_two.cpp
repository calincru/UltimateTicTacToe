// Self
#include "heuristic_two.hpp"

// Project
#include "square_pos_utils.hpp"
#include "utils.hpp"
#include "globals.hpp"

#define SET_CONTAINS(set, value) (set.find(value) != set.end())

namespace tictactoe {
namespace {
    // STATIC DATA
    static constexpr auto WON_FACTOR = 10000;
    static constexpr auto ALMOST_WON_FACTOR = 1000;
    static constexpr auto UNDECIDED_FACTOR = 100;
    static constexpr auto CANNOT_WIN_FACTOR = 10;
} // namespace {

///
// Returns WON_FACTOR or less, depending on the position of this small game
// inside the big game.
///
int heuristic_two::score_won_game(big_pos_e game) const {
    int num = 1;
    int denom = 1;

    switch (game) {
        ///
        //      Left|Mid|Right
        //      =============
        // Upper|   | x |   |
        //      -------------
        // Mid  | x |   | x |
        //      -------------
        // Lower|   | x |   |
        //      =============
        //
        // The score assigned is a little bit over 1/2 so that two such games
        // won on the same line/column are more valuable than winning the middle
        // one.
        ///
        case big_pos_e::UM:
        case big_pos_e::ML:
        case big_pos_e::MR:
        case big_pos_e::LM:
            num = 11;
            denom = 20;
            break;

        ///
        //      Left|Mid|Right
        //      =============
        // Upper| x |   | x |
        //      -------------
        // Mid  |   |   |   |
        //      -------------
        // Lower| x |   | x |
        //      =============
        ///
        case big_pos_e::UL:
        case big_pos_e::UR:
        case big_pos_e::LL:
        case big_pos_e::LR:
            num = 4;
            denom = 5;

        ///
        //      Left|Mid|Right
        //      =============
        // Upper|   |   |   |
        //      -------------
        // Mid  |   | x |   |
        //      -------------
        // Lower|   |   |   |
        //      =============
        ///
        case big_pos_e::MM:
            num = 1;
            denom = 1;
    }

    return num * WON_FACTOR / denom;
}

///
// FIXME How could an almost won game be "better" than another one, exception
// through the number of ways it can be won in (see score_and_classify_games).
///
int heuristic_two::score_almost_won_game(big_pos_e game) const {
    UNUSED(game);

    return ALMOST_WON_FACTOR;
}

///
// Return UNDECIDED_FACTOR balanced by the difference of own squares.
///
int heuristic_two::score_undecided_game(big_pos_e game) const {
    const auto denom = 5;
    auto mines = 0;
    auto his = 0;

    for (int i = 0; i < 9; ++i) {
        auto pos = square_pos_utils::coord_to_small_pos(i);
        auto owner = d_table.get_owner_of({game, pos});

        if (owner == d_player)
            ++mines;
        else if (owner == d_opponent)
            ++his;
    }

    return UNDECIDED_FACTOR + (mines - his) * UNDECIDED_FACTOR / denom;
}

///
// FIXME Same as "score_almost_won_game".
///
int heuristic_two::score_cannot_win_game(big_pos_e game) const {
    UNUSED(game);

    return CANNOT_WIN_FACTOR;
}

int heuristic_two::score_and_classify_games(game_types_arr &games) const {
    auto score = 0;

    for (auto i = 0; i < 9; ++i) {
        auto game = square_pos_utils::coord_to_big_pos(i);
        int almost_ret;

        if (d_table.is_small_won_by(d_player, game)) {
            score += score_won_game(game);
            games[WON].emplace(game);

        } else if (d_table.is_small_won_by(d_opponent, game)) {
            games[LOST].emplace(game);

        // Returns the number of ways in which this game can be won.
        //
        // E.g. it is 3 in the following game (we are X):
        //
        //      Left|Mid|Right
        //      =============
        // Upper| X |   | X |
        //      -------------
        // Mid  |   |   |   |
        //      -------------
        // Lower| X | O | O |
        //      =============
        //
        } else if ((almost_ret =
                        d_table.is_small_almost_won_by(d_player, game)) > 0) {
            score += almost_ret * score_almost_won_game(game);
            games[ALMOST_WON].emplace(game);

        } else if (!d_table.can_win_small(d_player, game)) {
            score += score_cannot_win_game(game);
            games[CANNOT_WIN].emplace(game);

        } else {
            score += score_undecided_game(game);
            games[UNDECIDED].emplace(game);
        }
    }

    return score;
}

///
// FIXME Adjust per winning line (row, column, diagonal) score here.
///
int heuristic_two::score_games_in_line(big_pos_e game1,
                                       big_pos_e game2,
                                       big_pos_e game3,
                                       const game_types_arr &games) const {
    UNUSED(game1);
    UNUSED(game2);
    UNUSED(game3);
    UNUSED(games);

    return 0;
}

heuristic_two::heuristic_two(const table_t &table,
                             const std::vector<big_pos_e> &avail,
                             player_e player)
    : heuristic_base{table, avail, player} {
    // Nothing to do
}

int heuristic_two::evaluate() const {
    auto games = game_types_arr{};
    auto score = score_and_classify_games(games);

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
