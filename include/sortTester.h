#ifndef SORTTESTER_H
#define SORTTESTER_H

#include "sorting.h"
#include "tester.h"

#include <vector>

class SortTester : public Tester {
  public:
    SortTester();
    void test() override;
    bool parseOpts(const int, const char **) override;

  private:
    enum struct SortOptions;
    Sorting sort;
    std::vector<bool> options;
    int size = 15;

    void printHelpMsg() const;
    bool validate() const;
    void runTest(void (Sorting::*)(), SortOptions) const;
    static std::string getSortingName(SortOptions);
};

#endif