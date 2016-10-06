#include "argumentParser.h"
#include "tester.h"

int main(int argc, const char **argv) {
    auto tester = parse(argc, argv);
    if (tester) tester->test();
    return 0;
}