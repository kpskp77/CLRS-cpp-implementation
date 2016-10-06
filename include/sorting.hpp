#include <type_traits>
#include <utility>
#include <vector>

// helper
namespace detail {
    auto less = [](auto const &lhs, auto const &rhs) { return lhs < rhs; };
} // namespace detail

/* Insertion sort
 * best: O(n); average: O(n^2); worst: O(n^2)
 */
template <class RandomIt> void insertSorting(RandomIt first, RandomIt last) {
    insertSorting(first, last, detail::less);
}

template <class RandomIt, class Compare>
void insertSorting(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    for (auto it = first + 1; it != last; ++it)
        for (auto iit = it; iit != first && comp(*iit, *(iit - 1)); --iit)
            swap(*(iit - 1), *iit);
}

/* Selection sort
 * best: O(n^2); average: O(n^2); worst: O(n^2)
 */
template <class RandomIt> void selectSorting(RandomIt first, RandomIt last) {
    selectSorting(first, last, detail::less);
}

template <class RandomIt, class Compare>
void selectSorting(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    for (; first != last - 1; ++first)
        for (auto it = first + 1; it != last; ++it)
            if (comp(*it, *first)) swap(*first, *it);
}

/* Bubble sort
 * best: O(n); average: O(n^2); worst: O(n^2)
 */
template <class RandomIt> void bubbleSorting(RandomIt first, RandomIt last) {
    bubbleSorting(first, last, detail::less);
}

template <class RandomIt, class Compare>
void bubbleSorting(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    auto swapped = true;
    while (swapped && --last != first) {
        swapped = false;
        for (auto it = first; it != last; ++it)
            if (comp(*(it + 1), *it)) {
                swap(*it, *(it + 1));
                swapped = true;
            }
    }
}

/* Merge sort
 * best: O(nlgn); average: O(nlgn); worst: O(nlgn)
 */
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
            } else if (*top2 < *top1) {
                d.push_back(std::move(*top2));
                ++top2;
            } else {
                d.push_back(std::move(*top1));
                ++top1;
            }
        }
        std::move(d.begin(), d.end(), first);
    }
} // namespace detail

template <class RandomIt> void mergeSorting(RandomIt first, RandomIt last) {
    mergeSorting(first, last, detail::less);
}

template <class RandomIt, class Compare>
void mergeSorting(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    if (last - first < 2) return;
    if (last - first == 2) {
        if (comp(*--last, *first)) swap(*first, *last);
    } else {
        auto middle = first + (last - first) / 2;
        mergeSorting(first, middle);
        mergeSorting(middle, last);
        detail::merge(first, middle, last);
    }
}

namespace detail {
    template <class RandomIt, class Index, class Compare>
    void maxHeapify(RandomIt first, RandomIt last, Index i, Compare comp) {
        using std::swap;
        auto left = 2 * i;
        if (left > last - first) return;
        auto right = 2 * i + 1;
        auto largest = i;
        if (comp(first[largest - 1], first[left - 1])) largest = left;
        if (right <= last - first && comp(first[largest - 1], first[right - 1]))
            largest = right;
        if (largest != i) {
            swap(first[i - 1], first[largest - 1]);
            maxHeapify(first, last, largest, comp);
        }
    }

    template <class RandomIt, class Compare>
    void buildMaxHeap(RandomIt first, RandomIt last, Compare comp) {
        for (auto i = (last - first) / 2; i > 0; --i) maxHeapify(first, last, i, comp);
    }
} // namespace detail

template <class RandomIt> void heapSorting(RandomIt first, RandomIt last) {
    heapSorting(first, last, detail::less);
}

template <class RandomIt, class Compare>
void heapSorting(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    detail::buildMaxHeap(first, last, comp);
    while (last - first > 1) {
        swap(*first, *--last);
        detail::maxHeapify(first, last, 1, comp);
    }
}