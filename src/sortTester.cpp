#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <string>

#include "sortTester.h"

enum struct SortTester::Option {
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

SortTester::SortTester() : options(static_cast<int>(Option::SIZE_COUNT), false) {}

void SortTester::test() {
    std::mt19937 randgen;
    randgen.seed(1);
    sort.reserve(size);
    for (auto i = size; i > 0; --i) {
        if (options[static_cast<int>(Option::RANDOM)]) sort.push_back(randgen());
        if (options[static_cast<int>(Option::BEST)]) sort.push_back(size - i + 1);
        if (options[static_cast<int>(Option::WORST)]) sort.push_back(i);
    }
    std::cout << "number of element: " << size << "\ttest mode: "
              << (options[static_cast<int>(Option::RANDOM)]
                      ? "random case"
                      : (options[static_cast<int>(Option::BEST)] ? "best case" : "worst case"))
              << '\n';

    if (options[static_cast<int>(Option::SHOWELEMENT)])
        std::cout << "Original data:\n" << sort << "\n\n";

    if (options[static_cast<int>(Option::INSERT)]) runTest(&Sorting::insertSorting, Option::INSERT);
    if (options[static_cast<int>(Option::SELECT)]) runTest(&Sorting::selectSorting, Option::SELECT);
    if (options[static_cast<int>(Option::BUBBLE)]) runTest(&Sorting::bubbleSorting, Option::BUBBLE);
    if (options[static_cast<int>(Option::MERGE)]) runTest(&Sorting::mergeSorting, Option::MERGE);
}

void SortTester::runTest(void (Sorting::*sorting)(), Option op) const {
    using timer = std::chrono::high_resolution_clock;
    auto local = sort;
    std::chrono::duration<double> diff;
    auto start = timer::now();
    (local.*sorting)();
    diff = timer::now() - start;
    std::cout << "time for " << getSortingName(op) << " sorting: " << diff.count() << " seconds\n";
    if (options[static_cast<int>(Option::SHOWELEMENT)])
        std::cout << "Sorted data:\n" << local << "\n\n";
}

bool SortTester::parseOpts(const int argc, const char **argv) {
    std::stack<std::string> args;
    for (auto i = argc - 1; i >= 0; --i) args.push(argv[i]);
    while (!args.empty()) {
        auto s = args.top();
        if (s.size() == 1 || s[0] != '-') return printHelpMsg();
        if (s[1] != '-') {
            for (auto it = s.cbegin() + 1; it != s.cend(); ++it) {
                switch (*it) {
                case 'm': options[static_cast<int>(Option::MERGE)] = true; break;
                case 'i': options[static_cast<int>(Option::INSERT)] = true; break;
                case 'b': options[static_cast<int>(Option::BUBBLE)] = true; break;
                case 's': options[static_cast<int>(Option::SELECT)] = true; break;
                case 'B': options[static_cast<int>(Option::BEST)] = true; break;
                case 'W': options[static_cast<int>(Option::WORST)] = true; break;
                case 'R': options[static_cast<int>(Option::RANDOM)] = true; break;
                case 'D': options[static_cast<int>(Option::SHOWELEMENT)] = true; break;
                default: return printHelpMsg();
                }
            }
        } else if (s == "--size") {
            args.pop();
            size = std::stoi(args.top());
        } else
            return printHelpMsg();
        args.pop();
    }
    return validate();
}

bool SortTester::validate() const {
    if (size < 1) {
        std::cout << "size must greater than 0!\n";
        return printHelpMsg();
    }
    if (options[static_cast<int>(Option::BEST)] + options[static_cast<int>(Option::RANDOM)] +
            options[static_cast<int>(Option::WORST)] !=
        1) {
        std::cout << "specify one and only one test mode!\n";
        return printHelpMsg();
    }
    if (!options[static_cast<int>(Option::MERGE)] && !options[static_cast<int>(Option::INSERT)] &&
        !options[static_cast<int>(Option::BUBBLE)] && !options[static_cast<int>(Option::SELECT)]) {
        std::cout << "specify at least one sorting algorithm for test!\n";
        return printHelpMsg();
    }
    return true;
}

bool SortTester::printHelpMsg() const {
    std::cout << "Usage:\n"
              << "\ttest sort <options>\n"
              << "\n\"options\":\n"
              << "\t-B  Set test mode as best case\n"
              << "\t-R  Set test mode as random case\n"
              << "\t-W  Set test mode as worst case\n"
              << "\t[Note: must specify one and only one test mode!]\n"
              << "\n\t-D  print the data before and after sorting\n"
              << "\n\t-i  test insert sorting\n"
              << "\t-s  test selection sorting\n"
              << "\t-b  test bubble sorting\n"
              << "\t-m  test merge sorting\n"
              << "\t[Note: specify at least one sorting algorithm to be tested.]\n"
              << "\n\t--size  set number of data to be sorted (default is 15)\n";
    return false;
}

std::string SortTester::getSortingName(SortTester::Option op) {
    switch (op) {
    case Option::INSERT: return "insert";
    case Option::SELECT: return "select";
    case Option::BUBBLE: return "bubble";
    case Option::MERGE: return "merge";
    default: return std::string();
    }
}