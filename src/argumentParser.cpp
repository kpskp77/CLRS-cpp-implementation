#include "argumentParser.h"
#include "sortTester.h"

std::unique_ptr<Tester> ArgumentParser::parse(int argc, const char **argv) {
    std::unique_ptr<Tester> tester;
    if (argc > 1) {
        std::string s(argv[1]);
        if (s == "sort") {
            tester = std::make_unique<SortTester>();
            if (tester->parseOpts(argc - 2, argv + 2))
                return tester;
            else {
                tester.release();
                return tester;
            }
        }
    } else
        printHelpMsg();

    return tester;
}

void ArgumentParser::printHelpMsg() const { std::cout << "help message\n"; }