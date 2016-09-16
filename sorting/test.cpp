#include <chrono>
#include <iostream>
#include <random>

#include "sorting.h"

using timer = std::chrono::high_resolution_clock;

int main() {
    std::mt19937 randgen;
    randgen.seed(1);
    constexpr auto size = 10000;
    Sorting d;
    d.reserve(size);
    for (auto i = size; i > 0; --i) {
        // if (i > size / 2)
        // d.push_back(i);
        // else
        //     d.push_back(-i - size);
        d.push_back(randgen());
    }
    // std::cout << d << '\n';

    std::chrono::duration<double> diff;
    auto start = timer::now();
    // d.insertSorting();
    // d.selectSorting();
    // d.bubbleSorting();
    d.mergeSorting();
    diff = timer::now() - start;
    std::cout << diff.count() << '\n';

    // std::cout << d << '\n';

    return 0;
}