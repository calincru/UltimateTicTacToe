#include <iostream>

int main() {
    int arr[1000] = {0,};

    for (auto &e : arr)
        std::cout << e << " ";
    std::cout << std::endl;
}
