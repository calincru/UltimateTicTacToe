#ifndef INCLUDED_SQUARE_POS_E_HPP
#define INCLUDED_SQUARE_POS_E_HPP 1

#include <functional>

namespace tictactoe {

// small_pos_e
enum class small_pos_e: unsigned char {
    UL, UM, UR,
    ML, MM, MR,
    LL, LM, LR
};

struct small_pos_hash_t {
    std::size_t operator()(small_pos_e pos) const {
        return static_cast<unsigned char>(pos);
    }
};

// big_pos_e
enum class big_pos_e: unsigned char {
    UL, UM, UR,
    ML, MM, MR,
    LL, LM, LR
};

struct big_pos_hash_t {
    std::size_t operator()(big_pos_e pos) const {
        return static_cast<unsigned char>(pos);
    }
};


// square_pos_t
struct square_pos_t {
    big_pos_e big;
    small_pos_e small;

    static square_pos_t from_coords(int row, int col) {
        return {static_cast<big_pos_e>(3*(row / 3 ) + col / 3),
                static_cast<small_pos_e>(3*(row % 3) + col % 3)};
    }

    static std::pair<int, int> to_coords(const square_pos_t& pos) {
        auto big = static_cast<unsigned char>(pos.big);
        auto small = static_cast<unsigned char>(pos.small);

        return {3*(big / 3) + small / 3,
                3*(big % 3) + small % 3};
    }
};

struct square_pos_hash_t {
    std::size_t operator()(const square_pos_t &pos) const {
        auto coords = square_pos_t::to_coords(pos);

        return std::hash<int>{}(coords.first * 9 + coords.second);
    }
};

// FREE OPERATORS
inline bool operator==(const square_pos_t &lhs, const square_pos_t &rhs) {
    return lhs.big == rhs.big && lhs.small == rhs.small;
}

inline bool operator!=(const square_pos_t &lhs, const square_pos_t &rhs) {
    return !(lhs == rhs);
}

} // namespace tictactoe
#endif // INCLUDED_SQUARE_POS_E_HPP
