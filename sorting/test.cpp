#include <chrono>
#include <iostream>
#include <random>

#include "sorting.h"

using timer = std::chrono::high_resolution_clock;

int main() {
    std::mt19937 randgen;
    randgen.seed(1);
    constexpr auto size = 15;
    std::chrono::duration<double> diff;
    Sorting d;
    for (auto i = size; i > 0; --i) {
        d.push_back(i);
        // d.push_back(randgen());
    }
    // std::cout << d << '\n';

    auto start = timer::now();
    // d.insertSorting();
    // d.selectSorting();
    d.bubbleSorting();
    diff = timer::now() - start;
    std::cout << diff.count() << '\n';

    std::cout << d << '\n';

    return 0;
}