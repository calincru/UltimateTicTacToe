// Self
#include "table_t.hpp"

namespace tictactoe {

bool table_t::check_owned_by(player_e player, big_pos_e pos) const {
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
            d_board.emplace(square_pos_t::from_coords(i, j), player_e::NONE);
        }
    }
}

player_e table_t::get_owner_of(square_pos_t pos) const {
    return d_board.at(pos);
}

bool table_t::is_won_by(player_e player, big_pos_e pos) const {
    return player == player_e::ME ? d_mines.find(pos) != d_mines.end()
                                  : d_his.find(pos) != d_his.end();
}

bool table_t::is_draw(big_pos_e pos) const {
    return d_draws.find(pos) != d_draws.end();
}

auto table_t::get_games_own_by(player_e player) const -> big_pos_set_t {
    return player == player_e::ME ? d_mines : d_his;
}

auto table_t::get_draws() const -> big_pos_set_t {
    return d_draws;
}

std::vector<small_pos_e> table_t::get_avail_moves_in(big_pos_e big) const {
    auto poses = std::vector<small_pos_e>{};

    for (auto i = 0; i < 9; ++i) {
        auto small = static_cast<small_pos_e>(i);

        if (get_owner_of({big, small}) == player_e::NONE) {
            poses.emplace_back(small);
        }
    }

    return poses;
}

void table_t::make_owned_by(player_e player, square_pos_t pos) {
    d_board[pos] = player;

    if (check_owned_by(player, pos.big)) {
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
