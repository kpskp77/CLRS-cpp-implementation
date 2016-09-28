#ifndef SORTTESTER_H
#define SORTTESTER_H

#include "tester.h"
#include <memory>

class SortTester : public Tester {
  public:
    SortTester();
    ~SortTester();
    void test() const override;
    bool parseOpts(const int, const char **) const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

#endif