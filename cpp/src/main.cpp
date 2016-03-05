// Project
#include "bot_t.hpp"

// C++
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Unfortunately <random> doesn't seem to work on their platform
    std::srand(std::time(nullptr));
    std::ios_base::sync_with_stdio(false);

    tictactoe::bot_t().play();
}
