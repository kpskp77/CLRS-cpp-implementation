#include "argumentParser.h"

int main(int argc, const char **argv) {
    auto tester = parse(argc, argv);
    if (tester) tester->test();
    return 0;
}

/* temp test for tmp
#include <iostream>
#include <string>
#include <vector>

#include "kmp.h"

int main() {
    std::ios::sync_with_stdio(false);
    int N;
    // swallow the trailing '\n'
    std::cin >> N >> std::ws;
    std::vector<int> counts(N, 0);
    std::vector<int> index(N, 0);

    for (int i = 0; i < N; ++i) {
        std::string str, pattern;
        std::getline(std::cin, pattern);
        std::getline(std::cin, str);
        counts[i] = KMP(str.cbegin(), str.cend(), pattern.cbegin(), pattern.cend());
        auto p = KMP(str.cbegin(), str.cend(), pattern.cbegin(), pattern.cend(), 2);
        index[i] = p == str.cend() ? -1 : p - str.cbegin();
    }
    for (int i = 0; i < N; ++i) { std::cout << counts[i] << '\t' << index[i] << '\n'; }
    return 0;
}
// */