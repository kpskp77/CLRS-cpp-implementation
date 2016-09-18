#include <iostream>

#include "argumentParser.h"
#include "sortTester.h"

std::unique_ptr<Tester> ArgumentParser::parse(int argc, const char **argv) {
    if (argc > 1) {
        std::string s(argv[1]);
        if (s == "sort") return parse<SortTester>(argc - 2, argv + 2);
    }
    printHelpMsg();
    return nullptr;
}

void ArgumentParser::printHelpMsg() const {
    std::cout << "Usage:\n"
              << "\ttest [category] <options>\n"
              << "\n\"category\"is one of:\n"
              << "\tsort - sort algorithms\n"
              << "\n\"options\":\n"
              << "depends on category. use\n"
              << "\ttest [category] -h\n"
              << "for details\n";
}

template <class T> std::unique_ptr<Tester> ArgumentParser::parse(int argc, const char **argv) {
    std::unique_ptr<Tester> tester = std::make_unique<T>();
    return tester->parseOpts(argc, argv) ? std::move(tester) : nullptr;
}