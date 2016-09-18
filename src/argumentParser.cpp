#include <iostream>

#include "argumentParser.h"
#include "sortTester.h"

std::unique_ptr<Tester> ArgumentParser::parse(int argc, const char **argv) {
    if (argc > 1) {
        std::string s(argv[1]);
        if (s == "sort") {
            auto tester = std::make_unique<SortTester>();
            return tester->parseOpts(argc - 2, argv + 2) ? std::move(tester) : nullptr;
        }
    }
    printHelpMsg();
    return nullptr;
}

void ArgumentParser::printHelpMsg() const {
    std::cout << "Usage:\n"
              << "\ttest [category] <options>\n\n"
              << "\"category\"is one of:\n"
              << "\t1. sort - sort algorithms\n\n"
              << "\"options\":\n"
              << "depends on category. use\n"
              << "\ttest [category] -h\n"
              << "for details\n";
}