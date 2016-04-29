#include <iostream>

int main() {
    int arr[1000] = {0,};

    for (auto &e : arr)
        std::cout << e << " ";
    std::cout << std::endl;

    for (auto &e : {1, 2, 3})
        std::cout << e << " ";
    std::cout << std::endl;
}
