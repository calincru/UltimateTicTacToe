// Self
#include "table_t.hpp"

// Project
#include "square_pos_utils.hpp"
#include "player_utils.hpp"
#include "utils.hpp"

namespace tictactoe {

bool table_t::check_game_won_by(player_e player) const {
        // Upper row
    return (is_small_won_by(player, big_pos_e::UL) &&
            is_small_won_by(player, big_pos_e::UM) &&
            is_small_won_by(player, big_pos_e::UR))

        // Middle row
        || (is_small_won_by(player, big_pos_e::ML) &&
            is_small_won_by(player, big_pos_e::MM) &&
            is_small_won_by(player, big_pos_e::MR))

        // Lower row
        || (is_small_won_by(player, big_pos_e::LL) &&
            is_small_won_by(player, big_pos_e::LM) &&
            is_small_won_by(player, big_pos_e::LR))

        // Left column
        || (is_small_won_by(player, big_pos_e::UL) &&
            is_small_won_by(player, big_pos_e::ML) &&
            is_small_won_by(player, big_pos_e::LL))

        // Middle column
        || (is_small_won_by(player, big_pos_e::UM) &&
            is_small_won_by(player, big_pos_e::MM) &&
            is_small_won_by(player, big_pos_e::LM))

        // Right column
        || (is_small_won_by(player, big_pos_e::UR) &&
            is_small_won_by(player, big_pos_e::MR) &&
            is_small_won_by(player, big_pos_e::LR))

        // UL - LR diagonal
        || (is_small_won_by(player, big_pos_e::UL) &&
            is_small_won_by(player, big_pos_e::MM) &&
            is_small_won_by(player, big_pos_e::LR))

        // UR - LL diagonal
        || (is_small_won_by(player, big_pos_e::UR) &&
            is_small_won_by(player, big_pos_e::MM) &&
            is_small_won_by(player, big_pos_e::LL));
};

bool table_t::check_small_won_by(player_e player, big_pos_e pos) const {
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
        || (d_board.at({pos, small_pos_e::UR}) == player &&
            d_board.at({pos, small_pos_e::MM}) == player &&
            d_board.at({pos, small_pos_e::LL}) == player);
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

player_e table_t::get_winner() const {
    if (check_game_won_by(player_e::ME)) {
        return player_e::ME;
    }
    if (check_game_won_by(player_e::OPPONENT)) {
        return player_e::OPPONENT;
    }

    return player_e::NONE;
}

player_e table_t::get_owner_of(square_pos_t pos) const {
    return d_board.at(pos);
}

int table_t::count_almost_won_by(player_e player, big_pos_e pos) const {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT,
               "is_small_almost_won_by precondition");

    auto score = [&](player_e p1, player_e p2, player_e p3) {
        auto opponent = player_utils::opponent(player);

        return (p1 == player) - (p1 == opponent)
             + (p2 == player) - (p2 == opponent)
             + (p3 == player) - (p3 == opponent);
    };

        // Upper row
    return (score(d_board.at({pos, small_pos_e::UL}),
                  d_board.at({pos, small_pos_e::UM}),
                  d_board.at({pos, small_pos_e::UR})) == 2)

        // Middle row
        + (score(d_board.at({pos, small_pos_e::ML}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::MR})) == 2)

        // Lower row
        + (score(d_board.at({pos, small_pos_e::LL}),
                 d_board.at({pos, small_pos_e::LM}),
                 d_board.at({pos, small_pos_e::LR})) == 2)

        // Left column
        + (score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::ML}),
                 d_board.at({pos, small_pos_e::LL})) == 2)

        // Middle column
        + (score(d_board.at({pos, small_pos_e::UM}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LM})) == 2)

        // Right column
        + (score(d_board.at({pos, small_pos_e::UR}),
                 d_board.at({pos, small_pos_e::MR}),
                 d_board.at({pos, small_pos_e::LR})) == 2)

        // UL - LR diagonal
        + (score(d_board.at({pos, small_pos_e::UL}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LR})) == 2)

        // UR - LL diagonal
        + (score(d_board.at({pos, small_pos_e::UR}),
                 d_board.at({pos, small_pos_e::MM}),
                 d_board.at({pos, small_pos_e::LL})) == 2);
}

bool table_t::is_small_won_by(player_e player, big_pos_e pos) const {
    TTT_ASSERT(player == player_e::ME || player == player_e::OPPONENT,
               "is_small_won_by precondition");
    return player == player_e::ME ? d_mines.find(pos) != d_mines.end()
                                  : d_his.find(pos) != d_his.end();
}

bool table_t::is_small_playable(big_pos_e game) const {
    // Check if the game was won by one of the players
    if (is_small_won_by(player_e::ME, game)
        || is_small_won_by(player_e::OPPONENT, game))
        return false;


    // Check if it is a draw
    for (int i = 0; i < 9; ++i) {
        auto small_pos = square_pos_utils::coord_to_small_pos(i);

        if (get_owner_of({game, small_pos}) == player_e::NONE) {
            return true;
        }
    }

    return false;
}

bool table_t::can_win_small(player_e player, big_pos_e game) const {
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
        || (d_board.at({game, small_pos_e::UR}) != opponent &&
            d_board.at({game, small_pos_e::MM}) != opponent &&
            d_board.at({game, small_pos_e::LL}) != opponent);
}

std::vector<small_pos_e> table_t::get_avail_moves_in(big_pos_e big) const {
    auto poses = std::vector<small_pos_e>{};

    TTT_ASSERT(is_small_playable(big), "get_avail_moves_in precondition");
    for (auto i = 0; i < 9; ++i) {
        auto small = square_pos_utils::coord_to_small_pos(i);

        if (get_owner_of({big, small}) == player_e::NONE) {
            poses.emplace_back(small);
        }
    }

    return poses;
}

std::vector<big_pos_e> table_t::get_next_available(big_pos_e pos) const {
    if (is_small_playable(pos)) {
        return {pos};
    }

    auto next_available = std::vector<big_pos_e>{};

    for (auto i = 0; i < 9; ++i) {
        auto game = square_pos_utils::coord_to_big_pos(i);

        if (game != pos && is_small_playable(game)) {
            next_available.emplace_back(game);
        }
    }

    return next_available;
}

void table_t::make_owned_by(player_e player, square_pos_t pos) {
    d_board[pos] = player;

    if (check_small_won_by(player, pos.big)) {
        if (player == player_e::ME) {
            d_mines.emplace(pos.big);
        } else {
            d_his.emplace(pos.big);
        }
    }
}

} // namespace tictactoe
