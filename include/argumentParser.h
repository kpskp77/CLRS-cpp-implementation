#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <memory>

#include "tester.h"

std::unique_ptr<Tester> parse(int, const char **);

#endif