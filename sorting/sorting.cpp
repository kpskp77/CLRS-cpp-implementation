#include "sorting.h"

void Sorting::insertSorting() {
    using std::swap;
    for (auto it = ++data_.begin(); it != data_.end(); ++it)
        for (auto iit = it; iit != data_.begin() && *(iit - 1) > *iit; --iit)
            swap(*(iit - 1), *iit);
}

void Sorting::selectSorting() {
    using std::swap;
    for (auto it = data_.begin(); it != data_.end() - 1; ++it)
        for (auto iit = it + 1; iit != data_.end(); ++iit)
            if (*it > *iit) swap(*it, *iit);
}

void Sorting::bubbleSorting() {
    using std::swap;
    bool swapped = true;
    for (auto it = --data_.end(); swapped && it != data_.begin(); --it) {
        swapped = false;
        for (auto iit = data_.begin(); iit != it; ++iit)
            if (*iit > *(iit + 1)) {
                swap(*iit, *(iit + 1));
                swapped = true;
            }
    }
}