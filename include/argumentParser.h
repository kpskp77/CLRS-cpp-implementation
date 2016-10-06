#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <memory>

class Tester;

std::unique_ptr<Tester> parse(int, const char **);

#endif