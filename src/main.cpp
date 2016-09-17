#include "argumentParser.h"

int main(int argc, const char **argv) {
    ArgumentParser parser;
    auto tester = parser.parse(argc, argv);
    if (tester) tester->test();
    return 0;
}