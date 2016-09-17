#ifndef SORTTESTER_H
#define SORTTESTER_H

#include "sorting.h"
#include "tester.h"

#include <map>

enum struct SortOptions { SIZE, SHOWELEMENT, INSERT, SELECT, BUBBLE, MERGE, BEST, RANDOM, WORST };

class SortTester : public Tester {
  public:
    SortTester();
    void test() override;
    bool parseOpts(const int, const char **) override;

  private:
    Sorting sort;
    std::map<SortOptions, int> options;

    void printHelpMsg() const;
    bool validate();
};

#endif