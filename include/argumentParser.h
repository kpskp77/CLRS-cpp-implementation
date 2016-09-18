#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <memory>

#include "tester.h"

class ArgumentParser {
  public:
    std::unique_ptr<Tester> parse(int, const char **);

  private:
    void printHelpMsg() const;
    template <class T> std::unique_ptr<Tester> parse(int, const char **);
};

#endif