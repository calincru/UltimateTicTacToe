// Self
#include "table_t.hpp"

// Project
#include "square_pos_utils.hpp"
#include "player_utils.hpp"
#include "utils.hpp"

namespace tictactoe {

bool table_t::check_won_by(player_e player, big_pos_e pos) const {
    // Upper row
    return (d_board.at({pos, small_pos_e::UL}) == player &&
            d_board.at({pos, small_pos_e::UM}) == player &&
            d_board.at({pos, small_pos_e::UR}) == player)

        // Middle row
        || (d_board.at({pos, small_pos_e::ML}) == player &&
            d_board.at({pos, small_pos_e::MM}) == player &&
            d_board.at({pos, small_pos_e::MR}) == player)

        // Lower row
        || (d_board.at({pos, small_pos_e::LL}) == player &&
            d_board.at({pos, small_pos_e::LM}) == player &&
            d_board.at({pos, small_pos_e::LR}) == player)

        // Left column
        || (d_board.at({pos, small_pos_e::UL}) == player &&
            d_board.at({pos, small_pos_e::ML}) == player &&
            d_board.at({pos, small_pos_e::LL}) == player)

        // Middle column
        || (d_board.at({pos, small_pos_e::UM}) == player &&
            d_board.at({pos, small_pos_e::MM}) == player &&
            d_board.at({pos, small_pos_e::LM}) == player)

        // Right column
        || (d_board.at({pos, small_pos_e::UR}) == player &&
            d_board.at({pos, small_pos_e::MR}) == player &&
            d_board.at({pos, small_pos_e::LR}) == player)

        // UL - LR diagonal
        || (d_board.at({pos, small_pos_e::UL}) == player &&
            d_board.at({pos, small_pos_e::MM}) == player &&
            d_board.at({pos, small_pos_e::LR}) == player)

        // UR - LL diagonal
        || (d_board.at({pos, small_pos_e::UL}) == player &&
            d_board.at({pos, small_pos_e::MM}) == player &&
            d_board.at({pos, small_pos_e::LR}) == player);
}

bool table_t::check_draw(big_pos_e pos) const {
    return !can_win(player_e::ME, pos) && !can_win(player_e::OPPONENT, pos);
}

table_t::table_t()
    : d_board(81) {
    for (auto i = 0; i < 9; ++i) {
        for (auto j = 0; j < 9; ++j) {
            d_board.emplace(square_pos_utils::coords_to_pos(i, j),
                            player_e::NONE);
        }
    }
}

player_e table_t::get_owner_of(square_pos_t pos) const {
    return d_board.at(pos);
}

bool table_t::is_won_by(player_e player, big_pos_e pos) const {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT);
    return player == player_e::ME ? d_mines.find(pos) != d_mines.end()
                                  : d_his.find(pos) != d_his.end();
}

bool table_t::is_almost_won_by(player_e player, big_pos_e pos) const {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT);

    auto score = [&](player_e p1, player_e p2, player_e p3) {
        auto other = player == player_e::ME ? player_e::OPPONENT
                                            : player_e::ME;

        return (p1 == player) - (p1 == other)
             + (p2 == player) - (p2 == other)
             + (p3 == player) - (p2 == other);
    };
        // Upper row
    return score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::UM}),
                 d_board.at({pos, small_pos_e::UR})) == 2

        // Middle row
        || score(d_board.at({pos, small_pos_e::ML}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::MR})) == 2

        // Lower row
        || score(d_board.at({pos, small_pos_e::LL}),
                 d_board.at({pos, small_pos_e::LM}),
                 d_board.at({pos, small_pos_e::LR})) == 2

        // Left column
        || score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::ML}),
                 d_board.at({pos, small_pos_e::LL})) == 2

        // Middle column
        || score(d_board.at({pos, small_pos_e::UM}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LM})) == 2

        // Right column
        || score(d_board.at({pos, small_pos_e::UR}),
                 d_board.at({pos, small_pos_e::MR}),
                 d_board.at({pos, small_pos_e::LR})) == 2

        // UL - LR diagonal
        || score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LR})) == 2

        // UR - LL diagonal
        || score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LR})) == 2;
}

bool table_t::is_draw(big_pos_e pos) const {
    return d_draws.find(pos) != d_draws.end();
}

bool table_t::is_playable(big_pos_e pos) const {
    return !is_won_by(player_e::ME, pos)
        && !is_won_by(player_e::OPPONENT, pos)
        && !is_draw(pos);
}

bool table_t::can_win(player_e player, big_pos_e game) const {
    auto opponent = player_utils::opponent(player);

    return (d_board.at({game, small_pos_e::UL}) != opponent &&
            d_board.at({game, small_pos_e::UM}) != opponent &&
            d_board.at({game, small_pos_e::UR}) != opponent)

        // Middle row
        || (d_board.at({game, small_pos_e::ML}) != opponent &&
            d_board.at({game, small_pos_e::MM}) != opponent &&
            d_board.at({game, small_pos_e::MR}) != opponent)

        // Lower row
        || (d_board.at({game, small_pos_e::LL}) != opponent &&
            d_board.at({game, small_pos_e::LM}) != opponent &&
            d_board.at({game, small_pos_e::LR}) != opponent)

        // Left column
        || (d_board.at({game, small_pos_e::UL}) != opponent &&
            d_board.at({game, small_pos_e::ML}) != opponent &&
            d_board.at({game, small_pos_e::LL}) != opponent)

        // Middle column
        || (d_board.at({game, small_pos_e::UM}) != opponent &&
            d_board.at({game, small_pos_e::MM}) != opponent &&
            d_board.at({game, small_pos_e::LM}) != opponent)

        // Right column
        || (d_board.at({game, small_pos_e::UR}) != opponent &&
            d_board.at({game, small_pos_e::MR}) != opponent &&
            d_board.at({game, small_pos_e::LR}) != opponent)

        // UL - LR diagonal
        || (d_board.at({game, small_pos_e::UL}) != opponent &&
            d_board.at({game, small_pos_e::MM}) != opponent &&
            d_board.at({game, small_pos_e::LR}) != opponent)

        // UR - LL diagonal
        || (d_board.at({game, small_pos_e::UL}) != opponent &&
            d_board.at({game, small_pos_e::MM}) != opponent &&
            d_board.at({game, small_pos_e::LR}) != opponent);
}

auto table_t::get_games_won_by(player_e player) const -> big_pos_set_t {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT);
    return player == player_e::ME ? d_mines : d_his;
}

auto table_t::get_draws() const -> big_pos_set_t {
    return d_draws;
}

auto table_t::get_playable() const -> big_pos_set_t {
    auto playable = big_pos_set_t{};

    for (auto i = 0; i < 9; ++i) {
        auto pos = square_pos_utils::coord_to_big_pos(i);

        if (is_playable(pos)) {
            playable.emplace(pos);
        }
    }

    return playable;
}

auto table_t::get_games_almost_won_by(player_e player) const -> big_pos_set_t {
    auto almost_won = big_pos_set_t{};

    for (auto i = 0; i < 9; ++i) {
        auto pos = square_pos_utils::coord_to_big_pos(i);

        if (is_almost_won_by(player, pos)) {
            almost_won.emplace(pos);
        }
    }

    return almost_won;
}

std::vector<small_pos_e> table_t::get_avail_moves_in(big_pos_e big) const {
    auto poses = std::vector<small_pos_e>{};

    for (auto i = 0; i < 9; ++i) {
        auto small = square_pos_utils::coord_to_small_pos(i);

        if (get_owner_of({big, small}) == player_e::NONE) {
            poses.emplace_back(small);
        }
    }

    return poses;
}

std::vector<big_pos_e> table_t::get_next_available(big_pos_e pos) const {
    if (is_playable(pos)) {
        return {pos};
    }

    auto next_available = std::vector<big_pos_e>{};

    for (auto i = 0; i < 9; ++i) {
        auto game = square_pos_utils::coord_to_big_pos(i);

        if (game != pos && is_playable(game)) {
            next_available.emplace_back(game);
        }
    }

    return next_available;
}

void table_t::make_owned_by(player_e player, square_pos_t pos) {
    d_board[pos] = player;

    if (check_won_by(player, pos.big)) {
        if (player == player_e::ME) {
            d_mines.emplace(pos.big);
        } else {
            d_his.emplace(pos.big);
        }
    } else if (check_draw(pos.big)) {
        d_draws.emplace(pos.big);
    }
}

} // namespace tictactoe
