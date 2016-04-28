#include <iostream>
#include <chrono>

int main() {
    auto start = std::chrono::steady_clock::now();
    volatile int sink = 0;

    for (int i = 0; i < 100000000; ++i)
        sink += 1;

    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << diff << " ms" << std::endl;
}
