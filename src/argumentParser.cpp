#include <iostream>

#include "argumentParser.h"
#include "kmpTester.h"
#include "sortTester.h"

static void printHelpMsg();
template <class T> static std::unique_ptr<Tester> parse(int, const char **);

std::unique_ptr<Tester> parse(int argc, const char **argv) {
    if (argc > 1) {
        std::string s(argv[1]);
        if (s == "sort") return parse<SortTester>(argc - 2, argv + 2);
        if (s == "kmp") return parse<KmpTester>(argc - 2, argv + 2);
    }
    printHelpMsg();
    return nullptr;
}

void printHelpMsg() {
    std::cout << "Usage:\n"
              << "\ttest [category] <options>\n"
              << "\n\"category\"is one of:\n"
              << "\tsort - sort algorithms\n"
              << "\tkmp - Knuth-Morris-Pratt algorithm\n"
              << "\n\"options\":\n"
              << "depends on category. use\n"
              << "\ttest [category] -h\n"
              << "for details\n";
}

template <class T> std::unique_ptr<Tester> parse(int argc, const char **argv) {
    std::unique_ptr<Tester> tester = std::make_unique<T>();
    return tester->parseOpts(argc, argv) ? std::move(tester) : nullptr;
}