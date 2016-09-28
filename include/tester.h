#ifndef TESTER_H
#define TESTER_H

class Tester {
  public:
    virtual ~Tester() {}
    virtual void test() const = 0;
    virtual bool parseOpts(const int, const char **) const = 0;
};

#endif