#ifndef PRIORITYQUEUETESTER_H
#define PRIORITYQUEUETESTER_H

#include "tester.h"
#include <memory>

class PriorityQueueTester : public Tester {
  public:
    PriorityQueueTester();
    ~PriorityQueueTester();
    void test() const override;
    bool parseOpts(const int, const char **) const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

#endif