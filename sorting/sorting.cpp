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
    auto swapped = true;
    while (swapped && --end != begin) {
        swapped = false;
        for (auto it = begin; it != end; ++it)
            if (*it > *(it + 1)) {
                swap(*it, *(it + 1));
                swapped = true;
            }
    }
}

void Sorting::mergeSorting(iterator begin, iterator end) {
    /* normal merge sorting implementation
    using std::swap;
    if (!isSorted(begin, end)) {
        if (end - begin == 2) {
            swap(*begin, *--end);
        } else {
            auto middle = begin + (end - begin) / 2;
            mergeSorting(begin, middle);
            mergeSorting(middle, end);
            merge(begin, middle, end);
        }
    }
    //--------------------------------------------------*/

    //* optimaze using insert sorting for small lenght
    if (end - begin <= 40) {
        insertSorting(begin, end);
    } else {
        auto middle = begin + (end - begin) / 2;
        mergeSorting(begin, middle);
        mergeSorting(middle, end);
        merge(begin, middle, end);
    }
    //--------------------------------------------------*/
}

void Sorting::merge(iterator begin, iterator middle, iterator end) {
    data_type d;
    d.reserve(end - begin);
    auto top1 = begin, top2 = middle;
    while (true) {
        if (top1 == middle) {
            break;
        } else if (top2 == end) {
            std::move_backward(top1, middle, end);
            break;
        } else if (*top1 > *top2) {
            d.push_back(std::move(*top2));
            ++top2;
        } else {
            d.push_back(std::move(*top1));
            ++top1;
        }
    }
    std::move(d.begin(), d.end(), begin);
}

bool Sorting::isSorted(iterator begin, iterator end) {
    auto sorted = true;
    while (++begin != end) { // has more than one element
        if (*(begin - 1) > *begin) {
            sorted = false;
            break;
        }
    }
    return sorted;
}