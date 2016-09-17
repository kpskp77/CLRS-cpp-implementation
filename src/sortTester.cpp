#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <string>

#include "sortTester.h"

using timer = std::chrono::high_resolution_clock;

SortTester::SortTester() {
    options[SortOptions::MERGE] = 0;
    options[SortOptions::INSERT] = 0;
    options[SortOptions::BUBBLE] = 0;
    options[SortOptions::SELECT] = 0;
    options[SortOptions::BEST] = 0;
    options[SortOptions::RANDOM] = 0;
    options[SortOptions::WORST] = 0;
    options[SortOptions::SIZE] = 100;
    options[SortOptions::SHOWELEMENT] = 0;
}

void SortTester::test() {
    std::mt19937 randgen;
    randgen.seed(1);
    auto size = options[SortOptions::SIZE];
    sort.reserve(size);
    for (auto i = size; i > 0; --i) {
        if (options[SortOptions::RANDOM]) sort.push_back(randgen());
        if (options[SortOptions::BEST]) sort.push_back(-i);
        if (options[SortOptions::WORST]) sort.push_back(i);
    }
    std::cout << "number of element: " << size << "\ttest mode: "
              << (options[SortOptions::RANDOM]
                      ? "random case"
                      : (options[SortOptions::BEST] ? "best case" : "worst case"))
              << '\n';

    if (options[SortOptions::SHOWELEMENT]) std::cout << "Original data:\n" << sort << "\n\n";
    std::chrono::duration<double> diff;
    if (options[SortOptions::INSERT]) {
        auto local = sort;
        auto start = timer::now();
        local.insertSorting();
        diff = timer::now() - start;
        std::cout << "time for insert sorting: " << diff.count() << " seconds\n";
        if (options[SortOptions::SHOWELEMENT]) std::cout << "Sorted data:\n" << local << "\n\n";
    }
    if (options[SortOptions::SELECT]) {
        auto local = sort;
        auto start = timer::now();
        local.selectSorting();
        diff = timer::now() - start;
        std::cout << "time for select sorting: " << diff.count() << " seconds\n";
        if (options[SortOptions::SHOWELEMENT]) std::cout << "Sorted data:\n" << local << "\n\n";
    }
    if (options[SortOptions::BUBBLE]) {
        auto local = sort;
        auto start = timer::now();
        local.bubbleSorting();
        diff = timer::now() - start;
        std::cout << "time for bubble sorting: " << diff.count() << " seconds\n";
        if (options[SortOptions::SHOWELEMENT]) std::cout << "Sorted data:\n" << local << "\n\n";
    }
    if (options[SortOptions::MERGE]) {
        auto local = sort;
        auto start = timer::now();
        local.mergeSorting();
        diff = timer::now() - start;
        std::cout << "time for merge sorting: " << diff.count() << " seconds\n";
        if (options[SortOptions::SHOWELEMENT]) std::cout << "Sorted data:\n" << local << "\n\n";
    }
}

bool SortTester::parseOpts(const int argc, const char **argv) {
    std::stack<std::string> args;
    for (auto i = argc - 1; i >= 0; --i) args.push(argv[i]);
    while (!args.empty()) {
        auto s = args.top();
        if (s.size() > 1) {
            if (s[0] == '-' && s[1] != '-') {
                for (auto it = s.cbegin() + 1; it != s.cend(); ++it) {
                    switch (*it) {
                    case 'm': options[SortOptions::MERGE] = 1; break;
                    case 'i': options[SortOptions::INSERT] = 1; break;
                    case 'b': options[SortOptions::BUBBLE] = 1; break;
                    case 's': options[SortOptions::SELECT] = 1; break;
                    case 'B': options[SortOptions::BEST] = 1; break;
                    case 'W': options[SortOptions::WORST] = 1; break;
                    case 'R': options[SortOptions::RANDOM] = 1; break;
                    case 'D': options[SortOptions::SHOWELEMENT] = 1; break;
                    default: printHelpMsg(); return false;
                    }
                }
            } else if (s[0] == '-' && s[1] == '-') {
                if (s == "--size") {
                    args.pop();
                    options[SortOptions::SIZE] = std::stoi(args.top());
                } else {
                    printHelpMsg();
                    return false;
                }
            }
        } else {
            printHelpMsg();
            return false;
        }
        args.pop();
    }
    return validate();
}

bool SortTester::validate() {
    if (options[SortOptions::SIZE] < 1) {
        std::cout << "size must greater than 0!\n";
        printHelpMsg();
        return false;
    }
    if (options[SortOptions::BEST] + options[SortOptions::RANDOM] + options[SortOptions::WORST] !=
        1) {
        std::cout << "specify one and only one test mode!\n";
        printHelpMsg();
        return false;
    }
    if (options[SortOptions::MERGE] + options[SortOptions::INSERT] + options[SortOptions::BUBBLE] +
            options[SortOptions::SELECT] ==
        0) {
        std::cout << "specify at least one sorting algorithm for test!\n";
        printHelpMsg();
        return false;
    }
    return true;
}

void SortTester::printHelpMsg() const { std::cout << "Help message\n"; }