#ifndef TESTER_H
#define TESTER_H

class Tester {
  public:
    virtual ~Tester() {}
    virtual void test() = 0;
    virtual bool parseOpts(const int, const char **) = 0;
};

#endif