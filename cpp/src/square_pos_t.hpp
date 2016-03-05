#ifndef INCLUDED_SQUARE_POS_E_HPP
#define INCLUDED_SQUARE_POS_E_HPP 1

#include <functional>

namespace tictactoe {

// small_pos_e
enum class small_pos_e {
    UL, UM, UR,
    ML, MM, MR,
    LL, LM, LR
};

struct small_pos_hash_t {
    std::size_t operator()(small_pos_e pos) const;
};

// big_pos_e
enum class big_pos_e {
    UL, UM, UR,
    ML, MM, MR,
    LL, LM, LR
};

struct big_pos_hash_t {
    std::size_t operator()(big_pos_e pos) const;
};

// square_pos_t
struct square_pos_t {
    big_pos_e big;
    small_pos_e small;
};

struct square_pos_hash_t {
    std::size_t operator()(const square_pos_t &pos) const;
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
