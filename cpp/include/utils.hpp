#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

// C++
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

namespace tictactoe {
namespace utils {

static inline std::vector<std::string> comma_split(const std::string &s) {
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

static inline std::string comma_join(const std::vector<std::string> &elems) {
    auto res = elems.front();

    for (auto it = elems.begin() + 1; it != elems.end(); ++it) {
        res += ',' + *it;
    }

    return res;
}

#define UNUSED(a) (void)(&a)

// Use assertions for now
#ifndef DEBUG
# define DEBUG
#endif

#ifdef DEBUG
# define TTT_ASSERT(assertion, description) \
    do { \
        if (!(assertion)) { \
            std::cerr << description << std::endl; \
        } \
        assert(assertion); \
    } while (false)

#else
# define TTT_ASSERT(assertion)
#endif

#ifdef DEBUG
# define TTT_DEBUG std::cerr
#else
# define TTT_DEBUG std::ostringstream{}
#endif

} // namespace utils
} // namespace tictactoe
#endif // UTILS_HPP_INCLUDED
