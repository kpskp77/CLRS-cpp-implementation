#ifndef SORTTESTER_H
#define SORTTESTER_H

#include "tester.h"
#include <memory>

class SortTester : public Tester {
  public:
    SortTester();
    ~SortTester();
    void test() override;
    bool parseOpts(const int, const char **) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

#endif