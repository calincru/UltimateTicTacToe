// Self
#include "table_t.hpp"

// Project
#include "square_pos_utils.hpp"
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

bool table_t::check_draw(big_pos_e) const {
    // TODO
    return false;
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

bool table_t::is_about_to_win(player_e player, big_pos_e pos) const {
        // Upper row
    return ((d_board.at({pos, small_pos_e::UL}) == player) +
            (d_board.at({pos, small_pos_e::UM}) == player) +
            (d_board.at({pos, small_pos_e::UR}) == player)) == 2

        // Middle row
        || ((d_board.at({pos, small_pos_e::ML}) == player) +
            (d_board.at({pos, small_pos_e::MM}) == player) +
            (d_board.at({pos, small_pos_e::MR}) == player)) == 2

        // Lower row
        || ((d_board.at({pos, small_pos_e::LL}) == player) +
            (d_board.at({pos, small_pos_e::LM}) == player) +
            (d_board.at({pos, small_pos_e::LR}) == player)) == 2

        // Left column
        || ((d_board.at({pos, small_pos_e::UL}) == player) +
            (d_board.at({pos, small_pos_e::ML}) == player) +
            (d_board.at({pos, small_pos_e::LL}) == player)) == 2

        // Middle column
        || ((d_board.at({pos, small_pos_e::UM}) == player) +
            (d_board.at({pos, small_pos_e::MM}) == player) +
            (d_board.at({pos, small_pos_e::LM}) == player)) == 2

        // Right column
        || ((d_board.at({pos, small_pos_e::UR}) == player) +
            (d_board.at({pos, small_pos_e::MR}) == player) +
            (d_board.at({pos, small_pos_e::LR}) == player)) == 2

        // UL - LR diagonal
        || ((d_board.at({pos, small_pos_e::UL}) == player) +
            (d_board.at({pos, small_pos_e::MM}) == player) +
            (d_board.at({pos, small_pos_e::LR}) == player)) == 2

        // UR - LL diagonal
        || ((d_board.at({pos, small_pos_e::UL}) == player) +
            (d_board.at({pos, small_pos_e::MM}) == player) +
            (d_board.at({pos, small_pos_e::LR}) == player)) == 2;
}

bool table_t::is_draw(big_pos_e pos) const {
    return d_draws.find(pos) != d_draws.end();
}

bool table_t::is_playable(big_pos_e pos) const {
    return !is_won_by(player_e::ME, pos)
        && !is_won_by(player_e::OPPONENT, pos)
        && !is_draw(pos);
}

auto table_t::get_games_own_by(player_e player) const -> big_pos_set_t {
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
