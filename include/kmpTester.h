#ifndef KMPTESTER_H
#define KMPTESTER_H

#include "tester.h"
#include <memory>

class KmpTester : public Tester {
  public:
    KmpTester();
    ~KmpTester();
    void test() const override;
    bool parseOpts(const int, const char **) const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

#endif