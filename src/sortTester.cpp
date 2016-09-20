#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <utility>

#include "sortTester.h"
#include "sorting.h"

struct SortTester::Impl {
    enum class Option {
        print = 0,
        best,
        random,
        worst,
        insert,
        select,
        bubble,
        merge,
        // futrue goes here
        end_mark
    };
    using option_t = uint32_t;
    constexpr static option_t printMask = 0x0001u, modeMask = 0x000eu, algorMask = 0x00f0u;

    friend Option &operator++(Option &op) {
        return op = op == Option::end_mark ? Option::print : Option(static_cast<int>(op) + 1);
    }

    // default: enalbe Option::print, test in Option::worst case,
    // enable all sort algorithms, number of data is 15
    Impl(option_t opts = 0x00f9u, int size = 15) : options(opts), size(size) {}

    static std::pair<void (Sorting::*)(), std::string> getAlgor(Option);
    static bool printHelpMsg();

    bool check(Option op) { return (options >> static_cast<int>(op)) & 0x0001u; }
    void runAlgorTest(Option);
    bool mergeOptions(option_t);

    Sorting sort;
    option_t options;
    int size;
};

SortTester::SortTester() : impl_(std::make_unique<Impl>()) {}

SortTester::~SortTester() {}

void SortTester::test() {
    std::mt19937 randgen;
    randgen.seed(1);
    impl_->sort.reserve(impl_->size);
    for (auto mode = Impl::Option::best; mode != Impl::Option::insert; ++mode) {
        if (!impl_->check(mode)) continue;
        std::cout << "======================================================\n";
        impl_->sort.clear();
        for (auto i = impl_->size; i > 0; --i) {
            if (mode == Impl::Option::random) impl_->sort.push_back(randgen());
            if (mode == Impl::Option::best) impl_->sort.push_back(impl_->size - i + 1);
            if (mode == Impl::Option::worst) impl_->sort.push_back(i);
        }
        std::cout << "number of element: " << impl_->size << "\ttest mode: "
                  << (mode == Impl::Option::random
                          ? "random case"
                          : (mode == Impl::Option::best ? "best case" : "worst case"))
                  << '\n';
        if (impl_->check(Impl::Option::print))
            std::cout << "Original data:\n" << impl_->sort << "\n\n";

        for (auto algor = Impl::Option::insert; algor != Impl::Option::end_mark; ++algor)
            if (impl_->check(algor)) impl_->runAlgorTest(algor);
    }
}

bool SortTester::parseOpts(const int argc, const char **argv) {
    std::stack<std::string> args;
    Impl::option_t op = 0u;
    for (auto i = argc - 1; i >= 0; --i) args.push(argv[i]);
    while (!args.empty()) {
        auto s = args.top();
        if (s.size() == 1 || s[0] != '-') return impl_->printHelpMsg();
        if (s[1] != '-') {
            for (auto it = s.cbegin() + 1; it != s.cend(); ++it) {
                switch (*it) {
                case 'P': op |= 0x01u << static_cast<int>(Impl::Option::print); break;
                case 'B': op |= 0x01u << static_cast<int>(Impl::Option::best); break;
                case 'R': op |= 0x01u << static_cast<int>(Impl::Option::random); break;
                case 'W': op |= 0x01u << static_cast<int>(Impl::Option::worst); break;
                case 'i': op |= 0x01u << static_cast<int>(Impl::Option::insert); break;
                case 's': op |= 0x01u << static_cast<int>(Impl::Option::select); break;
                case 'b': op |= 0x01u << static_cast<int>(Impl::Option::bubble); break;
                case 'm': op |= 0x01u << static_cast<int>(Impl::Option::merge); break;
                default: return impl_->printHelpMsg();
                }
            }
        } else if (s == "--size") {
            args.pop();
            impl_->size = std::stoi(args.top());
        } else
            return impl_->printHelpMsg();
        args.pop();
    }
    return impl_->mergeOptions(op);
}

void SortTester::Impl::runAlgorTest(Option algor) {
    using timer = std::chrono::high_resolution_clock;
    auto localSort = sort;
    auto algorPair = getAlgor(algor);
    std::chrono::duration<double> diff;
    auto start = timer::now();
    (localSort.*algorPair.first)();
    diff = timer::now() - start;
    std::cout << "time for " << algorPair.second << " sorting: " << diff.count()
              << " seconds\n";
    if (check(Option::print)) std::cout << "Sorted data:\n" << localSort << "\n\n";
}

bool SortTester::Impl::mergeOptions(option_t op) {
    if (size < 1) {
        std::cout << "size must greater than 0!\n";
        return printHelpMsg();
    }
    // if not explicitly enable some options, use default
    if (op & modeMask) options = (op | ~modeMask) & (options | modeMask);
    if (op & algorMask) options = (op | ~algorMask) & (options | algorMask);
    // if not explicitly trun on printing element and size is too big, turn off printing
    if (size > 20) options &= op | ~printMask;
    return true;
}

std::pair<void (Sorting::*)(), std::string> SortTester::Impl::getAlgor(Option algor) {
    switch (algor) {
    case Option::insert:
        return std::pair<void (Sorting::*)(), std::string>(&Sorting::insertSorting, "insert");
    case Option::select:
        return std::pair<void (Sorting::*)(), std::string>(&Sorting::selectSorting, "select");
    case Option::bubble:
        return std::pair<void (Sorting::*)(), std::string>(&Sorting::bubbleSorting, "bubble");
    case Option::merge:
        return std::pair<void (Sorting::*)(), std::string>(&Sorting::mergeSorting, "merge");
    default: throw 7;
    }
}

bool SortTester::Impl::printHelpMsg() {
    std::cout
        << "Usage:\n"
        << "\ttest sort <options>\n"
        << "\n\"options\":\n"
        << "\t-B  Set test mode as best case\n"
        << "\t-R  Set test mode as random case\n"
        << "\t-W  Set test mode as worst case\n"
        << "\t[Note: must specify one and only one test mode! default is worst case]\n"
        << "\n\t-P  print the data before and after sorting (default is on for size <= 20, "
           "off otherwise)\n"
        << "\n\t-i  test insert sorting\n"
        << "\t-s  test selection sorting\n"
        << "\t-b  test bubble sorting\n"
        << "\t-m  test merge sorting\n"
        << "\t[Note: defult is all on]\n"
        << "\n\t--size  set number of data to be sorted (default is 15)\n";
    return false;
}