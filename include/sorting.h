#ifndef SORTING_H
#define SORTING_H

#include <type_traits>
#include <utility>
#include <vector>

// sorting algorithms
template <class RandomIt> void insertSorting(RandomIt first, RandomIt last);
template <class RandomIt> void selectSorting(RandomIt first, RandomIt last);
template <class RandomIt> void bubbleSorting(RandomIt first, RandomIt last);
template <class RandomIt> void mergeSorting(RandomIt first, RandomIt last);

// helper
namespace detail {
    template <class RandomIt> void merge(RandomIt first, RandomIt middle, RandomIt last);
    template <class RandomIt> bool isSorted(RandomIt first, RandomIt last);
} // namespace detail

// implementation
template <class RandomIt> void insertSorting(RandomIt first, RandomIt last) {
    using std::swap;
    for (auto it = first + 1; it != last; ++it)
        for (auto iit = it; iit != first && *(iit - 1) > *iit; --iit) swap(*(iit - 1), *iit);
}

template <class RandomIt> void selectSorting(RandomIt first, RandomIt last) {
    using std::swap;
    for (; first != last - 1; ++first)
        for (auto it = first + 1; it != last; ++it)
            if (*first > *it) swap(*first, *it);
}

template <class RandomIt> void bubbleSorting(RandomIt first, RandomIt last) {
    using std::swap;
    auto swapped = true;
    while (swapped && --last != first) {
        swapped = false;
        for (auto it = first; it != last; ++it)
            if (*it > *(it + 1)) {
                swap(*it, *(it + 1));
                swapped = true;
            }
    }
}

template <class RandomIt> void mergeSorting(RandomIt first, RandomIt last) {
    /* normal merge sorting implementation
    using std::swap;
    if (!detail::isSorted(first, last)) {
        if (last - first == 2) {
            swap(*first, *--last);
        } else {
            auto middle = first + (last - first) / 2;
            mergeSorting(first, middle);
            mergeSorting(middle, last);
            merge(first, middle, last);
        }
    }
    //--------------------------------------------------*/

    //* optimaze using insert sorting for small lenght
    if (last - first <= 40) {
        insertSorting(first, last);
    } else {
        auto middle = first + (last - first) / 2;
        mergeSorting(first, middle);
        mergeSorting(middle, last);
        detail::merge(first, middle, last);
    }
    //--------------------------------------------------*/
}

namespace detail {
    template <class RandomIt> void merge(RandomIt first, RandomIt middle, RandomIt last) {
        std::vector<std::decay_t<decltype(*first)>> d;
        d.reserve(last - first);
        auto top1 = first, top2 = middle;
        while (true) {
            if (top1 == middle) {
                break;
            } else if (top2 == last) {
                std::move_backward(top1, middle, last);
                break;
            } else if (*top1 > *top2) {
                d.push_back(std::move(*top2));
                ++top2;
            } else {
                d.push_back(std::move(*top1));
                ++top1;
            }
        }
        std::move(d.begin(), d.end(), first);
    }
    template <class RandomIt> bool isSorted(RandomIt first, RandomIt last) {
        auto sorted = true;
        while (++first != last) { // has more than one element
            if (*(first - 1) > *first) {
                sorted = false;
                break;
            }
        }
        return sorted;
    }
} // namespace detail

#endif