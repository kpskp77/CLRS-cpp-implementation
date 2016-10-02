#ifndef KMP_H
#define KMP_H

/* Knuth–Morris–Pratt algorithm
 * need random access iterator
 * the type iterator refers to should have operator==
 */

#include <cstddef>

// return times pattern matches in main
// the case "ABA" in "ABABA" is considered as matching two times
template <class RandomIt>
std::size_t KMP(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
                RandomIt patternLast);

// return the position in main where the xth match begins, or
// return mainLast if no match or xth is larger than the actual times of match
// the index of second match of "ABA" in "ABABA" is considered at 2 (starting at 0)
template <class RandomIt>
RandomIt KMP(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
             RandomIt patternLast, std::size_t xth);

#include "kmp.hpp"

#endif