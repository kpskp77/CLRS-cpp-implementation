#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <string>

#include "sortTester.h"

using timer = std::chrono::high_resolution_clock;

enum struct SortTester::SortOptions {
    SHOWELEMENT = 0,
    BEST,
    RANDOM,
    WORST,
    INSERT,
    SELECT,
    BUBBLE,
    MERGE,
    SIZE_COUNT
};

SortTester::SortTester() : options(static_cast<int>(SortOptions::SIZE_COUNT), false) {}

void SortTester::test() {
    std::mt19937 randgen;
    randgen.seed(1);
    sort.reserve(size);
    for (auto i = size; i > 0; --i) {
        if (options[static_cast<int>(SortOptions::RANDOM)]) sort.push_back(randgen());
        if (options[static_cast<int>(SortOptions::BEST)]) sort.push_back(-i);
        if (options[static_cast<int>(SortOptions::WORST)]) sort.push_back(i);
    }
    std::cout << "number of element: " << size << "\ttest mode: "
              << (options[static_cast<int>(SortOptions::RANDOM)]
                      ? "random case"
                      : (options[static_cast<int>(SortOptions::BEST)] ? "best case" : "worst case"))
              << '\n';

    if (options[static_cast<int>(SortOptions::SHOWELEMENT)])
        std::cout << "Original data:\n" << sort << "\n\n";

    if (options[static_cast<int>(SortOptions::INSERT)])
        runTest(&Sorting::insertSorting, SortOptions::INSERT);
    if (options[static_cast<int>(SortOptions::SELECT)])
        runTest(&Sorting::selectSorting, SortOptions::SELECT);
    if (options[static_cast<int>(SortOptions::BUBBLE)])
        runTest(&Sorting::bubbleSorting, SortOptions::BUBBLE);
    if (options[static_cast<int>(SortOptions::MERGE)])
        runTest(&Sorting::mergeSorting, SortOptions::MERGE);
}

void SortTester::runTest(void (Sorting::*sorting)(), SortOptions op) const {
    auto local = sort;
    std::chrono::duration<double> diff;
    auto start = timer::now();
    (local.*sorting)();
    diff = timer::now() - start;
    std::cout << "time for " << getSortingName(op) << " sorting: " << diff.count() << " seconds\n";
    if (options[static_cast<int>(SortOptions::SHOWELEMENT)])
        std::cout << "Sorted data:\n" << local << "\n\n";
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
                    case 'm': options[static_cast<int>(SortOptions::MERGE)] = true; break;
                    case 'i': options[static_cast<int>(SortOptions::INSERT)] = true; break;
                    case 'b': options[static_cast<int>(SortOptions::BUBBLE)] = true; break;
                    case 's': options[static_cast<int>(SortOptions::SELECT)] = true; break;
                    case 'B': options[static_cast<int>(SortOptions::BEST)] = true; break;
                    case 'W': options[static_cast<int>(SortOptions::WORST)] = true; break;
                    case 'R': options[static_cast<int>(SortOptions::RANDOM)] = true; break;
                    case 'D': options[static_cast<int>(SortOptions::SHOWELEMENT)] = true; break;
                    default: printHelpMsg(); return false;
                    }
                }
            } else if (s[0] == '-' && s[1] == '-') {
                if (s == "--size") {
                    args.pop();
                    size = std::stoi(args.top());
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

bool SortTester::validate() const {
    if (size < 1) {
        std::cout << "size must greater than 0!\n";
        printHelpMsg();
        return false;
    }
    if (options[static_cast<int>(SortOptions::BEST)] +
            options[static_cast<int>(SortOptions::RANDOM)] +
            options[static_cast<int>(SortOptions::WORST)] !=
        1) {
        std::cout << "specify one and only one test mode!\n";
        printHelpMsg();
        return false;
    }
    if (!options[static_cast<int>(SortOptions::MERGE)] &&
        !options[static_cast<int>(SortOptions::INSERT)] &&
        !options[static_cast<int>(SortOptions::BUBBLE)] &&
        !options[static_cast<int>(SortOptions::SELECT)]) {
        std::cout << "specify at least one sorting algorithm for test!\n";
        printHelpMsg();
        return false;
    }
    return true;
}

void SortTester::printHelpMsg() const {
    std::cout << "Usage:\n"
              << "\ttest sort <options>\n\n"
              << "\"options\":\n"
              << "\t-B  Set test mode as best case\n"
              << "\t-R  Set test mode as random case\n"
              << "\t-W  Set test mode as worst case\n"
              << "\t[Note: must specify one and only one test mode!]\n\n"
              << "\t-D  print the data before and after sorting\n\n"
              << "\t-i  test insert sorting\n"
              << "\t-s  test selection sorting\n"
              << "\t-b  test bubble sorting\n"
              << "\t-m  test merge sorting\n"
              << "\t[Note: specify at least one sorting algorithm to be tested.]\n\n"
              << "\t--size  set number of data to be sorted\n";
}

std::string getSortingName(SortTester::SortOptions op) {
    switch (op) {
    case SortTester::SortOptions::INSERT: return "insert";
    case SortTester::SortOptions::SELECT: return "select";
    case SortTester::SortOptions::BUBBLE: return "bubble";
    case SortTester::SortOptions::MERGE: return "merge";
    default: return std::string();
    }
}