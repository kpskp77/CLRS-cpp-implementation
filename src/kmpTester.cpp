#include <chrono>
#include <iostream>
#include <string>

#include "kmp.h"
#include "kmpTester.h"

namespace /* unnamed */ {
    bool printHelpMsg();
} // namespace  /* unnamed */

struct KmpTester::Impl {
    std::string main_;
    std::string pattern_;
};

KmpTester::KmpTester() : impl_(std::make_unique<Impl>()) {}

KmpTester::~KmpTester() {}

void KmpTester::test() const {
    using timer = std::chrono::high_resolution_clock;
    std::chrono::duration<double> diff;

    std::ios::sync_with_stdio(false);
    std::cout << "input the main string:\n";
    std::getline(std::cin, impl_->main_);

    std::cout << "input the pattern string:\n";
    std::getline(std::cin, impl_->pattern_);

    auto start = timer::now();
    auto count = KMP(impl_->main_.cbegin(), impl_->main_.cend(), impl_->pattern_.cbegin(),
                     impl_->pattern_.cend());
    diff = timer::now() - start;

    std::cout << "\nmatching finished in " << diff.count() << " seconds\n";
    std::cout << "counts of pattern matches in main: " << count << '\n';

    if (count == 0) return;
    std::cout << "index of all matches begin at:\n";
    for (decltype(count) i = 1; i <= count; ++i)
        std::cout << KMP(impl_->main_.cbegin(), impl_->main_.cend(), impl_->pattern_.cbegin(),
                         impl_->pattern_.cend(), i) -
                         impl_->main_.cbegin()
                  << ' ';
}

bool KmpTester::parseOpts(const int argc, const char **argv) const {
    return argc == 0 ? true : printHelpMsg();
}

namespace /* unnamed */ {
    bool printHelpMsg() {
        std::cout << "Usage:\n"
                  << "\ttest kmp\n";
        return false;
    }
} // namespace  /* unnamed */
