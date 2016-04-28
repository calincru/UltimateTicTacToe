#ifndef INCLUDED_COMMON_GLOBALS_HPP
#define INCLUDED_COMMON_GLOBALS_HPP 1

// C++
#include <chrono>

namespace tictactoe {

// CONSTANTS
static constexpr auto INF = 0x3f3f3f3f;
static constexpr auto TIME_PER_ROUND = 500;
static constexpr auto TIMEBANK = 10000;

// TYPES
using duration_t = std::chrono::milliseconds;

} // namespace tictactoe
#endif // INCLUDED_COMMON_GLOBALS_HPP
