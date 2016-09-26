#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "sortTester.h"
#include "sorting.h"

namespace /* unnamed */ {
    class Test;
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
    using element_type = int;
    using data_type = std::vector<element_type>;

    constexpr option_t printMask = 0x0001u, modeMask = 0x000eu, algorMask = 0x00f0u;

    Option &operator++(Option &op) {
        return op = op == Option::end_mark ? Option::print : Option(static_cast<int>(op) + 1);
    }
    bool printHelpMsg();
    std::ostream &operator<<(std::ostream &, data_type const &);
} // namespace  /* unnamed */

struct SortTester::Impl {
    // default: enalbe Option::print, test in Option::worst case,
    // enable all sort algorithms, number of data is 15
    Impl(option_t opts = 0x00f9u, int size = 15) : options(opts), size(size) {}

    bool check(Option op) { return (options >> static_cast<int>(op)) & 0x0001u; }
    void runAlgorTest(Option);
    bool mergeOptions(option_t);

    data_type data_;
    option_t options;
    int size;
};

SortTester::SortTester() : impl_(std::make_unique<Impl>()) {}

SortTester::~SortTester() {}

void SortTester::test() {
    std::mt19937 randgen;
    randgen.seed(1);
    impl_->data_.reserve(impl_->size);
    for (auto mode = Option::best; mode != Option::insert; ++mode) {
        if (!impl_->check(mode)) continue;
        std::cout << "======================================================\n";
        impl_->data_.clear();
        for (auto i = impl_->size; i > 0; --i) {
            if (mode == Option::random) impl_->data_.push_back(randgen());
            if (mode == Option::best) impl_->data_.push_back(impl_->size - i + 1);
            if (mode == Option::worst) impl_->data_.push_back(i);
        }
        std::cout << "number of element: " << impl_->size << "\ttest mode: "
                  << (mode == Option::random
                          ? "random case"
                          : (mode == Option::best ? "best case" : "worst case"))
                  << '\n';
        if (impl_->check(Option::print))
            std::cout << "Original data:\n" << impl_->data_ << "\n\n";

        for (auto algor = Option::insert; algor != Option::end_mark; ++algor)
            if (impl_->check(algor)) impl_->runAlgorTest(algor);
    }
}

void SortTester::Impl::runAlgorTest(Option algor) {
    using timer = std::chrono::high_resolution_clock;
    auto data = data_;
    std::string algorName;
    std::chrono::duration<double> diff;
    auto start = timer::now();
    switch (algor) {
    case Option::insert:
        insertSorting(data.begin(), data.end());
        algorName = "insert";
        break;
    case Option::select:
        selectSorting(data.begin(), data.end());
        algorName = "select";
        break;
    case Option::bubble:
        bubbleSorting(data.begin(), data.end());
        algorName = "bubble";
        break;
    case Option::merge:
        mergeSorting(data.begin(), data.end());
        algorName = "merge";
        break;
    default: throw 7;
    }
    diff = timer::now() - start;
    std::cout << "time for " << algorName << " sorting: " << diff.count() << " seconds\n";
    if (check(Option::print)) std::cout << "Sorted data:\n" << data << "\n\n";
}

bool SortTester::parseOpts(const int argc, const char **argv) {
    std::stack<std::string> args;
    option_t op = 0u;
    for (auto i = argc - 1; i >= 0; --i) args.push(argv[i]);
    while (!args.empty()) {
        auto s = args.top();
        if (s.size() == 1 || s[0] != '-') return printHelpMsg();
        if (s[1] != '-') {
            for (auto it = s.cbegin() + 1; it != s.cend(); ++it) {
                switch (*it) {
                case 'P': op |= 0x01u << static_cast<int>(Option::print); break;
                case 'B': op |= 0x01u << static_cast<int>(Option::best); break;
                case 'R': op |= 0x01u << static_cast<int>(Option::random); break;
                case 'W': op |= 0x01u << static_cast<int>(Option::worst); break;
                case 'i': op |= 0x01u << static_cast<int>(Option::insert); break;
                case 's': op |= 0x01u << static_cast<int>(Option::select); break;
                case 'b': op |= 0x01u << static_cast<int>(Option::bubble); break;
                case 'm': op |= 0x01u << static_cast<int>(Option::merge); break;
                default: return printHelpMsg();
                }
            }
        } else if (s == "--size") {
            args.pop();
            impl_->size = std::stoi(args.top());
        } else
            return printHelpMsg();
        args.pop();
    }
    return impl_->mergeOptions(op);
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

namespace /* unnamed */ {
    bool printHelpMsg() {
        std::cout
            << "Usage:\n"
            << "\ttest sort <options>\n"
            << "\n\"options\":\n"
            << "\t-B  Set test mode as best case\n"
            << "\t-R  Set test mode as random case\n"
            << "\t-W  Set test mode as worst case\n"
            << "\t[Note: must specify one and only one test mode! default is worst case]\n"
            << "\n\t-P  print the data before and after sorting (default is on for size <= "
               "20, off otherwise)\n"
            << "\n\t-i  test insert sorting\n"
            << "\t-s  test selection sorting\n"
            << "\t-b  test bubble sorting\n"
            << "\t-m  test merge sorting\n"
            << "\t[Note: defult is all on]\n"
            << "\n\t--size  set number of data to be sorted (default is 15)\n";
        return false;
    }

    std::ostream &operator<<(std::ostream &os, data_type const &data) {
        for (auto const &i : data) os << i << '\t';
        return os;
    }

    /* test for user-defined type
    class Test {
      public:
        Test(int i) : i(new int(i)) {}
        Test(Test const &t) : i(new int(*t.i)) { std::cout << "Test(Test const &)\n"; }
        Test(Test &&t) noexcept : i(t.i) {
            t.i = nullptr;
            std::cout << "Test(Test &&)\n";
        }
        ~Test() noexcept { delete i; }
        Test &operator=(Test const &t) {
            *i = *t.i;
            return *this;
        }
        Test &operator=(Test &&t) noexcept {
            i = t.i;
            t.i = nullptr;
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, Test const &t) {
            os << *t.i;
            return os;
        }
        friend bool operator>(Test const &t1, Test const &t2) { return *t1.i > *t2.i; }

      private:
        int *i;
    };
    //-----------------------------------------------------------------------*/
} // namespace  /* unnamed */
