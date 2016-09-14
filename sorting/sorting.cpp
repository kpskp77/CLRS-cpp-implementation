#include "sorting.h"

void Sorting::insertSorting(iterator begin, iterator end) {
    using std::swap;
    for (auto it = begin + 1; it != end; ++it)
        for (auto iit = it; iit != begin && *(iit - 1) > *iit; --iit) swap(*(iit - 1), *iit);
}

void Sorting::selectSorting(iterator begin, iterator end) {
    using std::swap;
    for (; begin != end - 1; ++begin)
        for (auto it = begin + 1; it != end; ++it)
            if (*begin > *it) swap(*begin, *it);
}

void Sorting::bubbleSorting(iterator begin, iterator end) {
    using std::swap;
    bool swapped = true;
    for (--end; swapped && end != begin; --end) {
        swapped = false;
        for (auto it = begin; it != end; ++it)
            if (*it > *(it + 1)) {
                swap(*it, *(it + 1));
                swapped = true;
            }
    }
}