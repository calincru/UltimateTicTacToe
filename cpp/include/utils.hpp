#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

// C++
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

namespace tictactoe {
namespace utils {

inline std::vector<std::string> comma_split(const std::string &s) {
    std::istringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;

    while (std::getline(ss, item, ',')) {
        if (!item.empty()) {
            tokens.emplace_back(item);
        }
    }

    return tokens;
}

inline std::string comma_join(const std::vector<std::string> &elems) {
    auto res = elems.front();

    for (auto it = elems.begin() + 1; it != elems.end(); ++it) {
        res += ',' + *it;
    }

    return res;
}

#define UNUSED(a) (void)(&a)

/* #ifdef DEBUG */
# define TTT_ASSERT(assertion) assert(assertion)
/* #else */
/* # define TTT_ASSERT(assertion) */
/* #endif */

} // namespace utils
} // namespace tictactoe
#endif // UTILS_HPP_INCLUDED
