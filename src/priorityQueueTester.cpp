#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

#include "priorityQueue.h"
#include "priorityQueueTester.h"

namespace /* unnamed */ {
    bool printHelpMsg();
} // namespace  /* unnamed */

struct PriorityQueueTester::Impl {
    MaxPriorityQueue<int> maxQueue;
};

PriorityQueueTester::PriorityQueueTester() : impl_(std::make_unique<Impl>()) {}

PriorityQueueTester::~PriorityQueueTester() {}

void PriorityQueueTester::test() const {
    for (int i = 0; i < 100; ++i) impl_->maxQueue.insert(i);
    std::cout << impl_->maxQueue << '\n';
}

bool PriorityQueueTester::parseOpts(const int argc, const char **argv) const {
    return argc == 0 ? true : printHelpMsg();
}

namespace /* unnamed */ {
    bool printHelpMsg() {
        std::cout << "Usage:\n"
                  << "\ttest kmp\n";
        return false;
    }
} // namespace  /* unnamed */
