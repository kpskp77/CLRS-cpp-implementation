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
template <class RandomIt> void insertSort(RandomIt first, RandomIt last) {
    insertSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void insertSort(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    for (auto it = first + 1; it != last; ++it)
        for (auto iit = it; iit != first && comp(*iit, *(iit - 1)); --iit)
            swap(*(iit - 1), *iit);
}

/* Selection sort
 * best: O(n^2); average: O(n^2); worst: O(n^2)
 */
template <class RandomIt> void selectSort(RandomIt first, RandomIt last) {
    selectSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void selectSort(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    for (; first != last - 1; ++first)
        for (auto it = first + 1; it != last; ++it)
            if (comp(*it, *first)) swap(*first, *it);
}

/* Bubble sort
 * best: O(n); average: O(n^2); worst: O(n^2)
 */
template <class RandomIt> void bubbleSort(RandomIt first, RandomIt last) {
    bubbleSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void bubbleSort(RandomIt first, RandomIt last, Compare comp) {
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
    template <class RandomIt, class Compare>
    void merge(RandomIt first, RandomIt middle, RandomIt last, Compare comp) {
        std::vector<std::decay_t<decltype(*first)>> d;
        d.reserve(last - first);
        auto top1 = first, top2 = middle;
        while (top1 != middle && top2 != last) {
            if (comp(*top2, *top1))
                d.push_back(std::move(*top2++));
            else
                d.push_back(std::move(*top1++));
        }
        // move [top1, middle) to [last - (middle - top1), last) if top2 reaches end
        if (top2 == last) std::move_backward(top1, middle, last);
        std::move(d.begin(), d.end(), first);
    }
} // namespace detail

template <class RandomIt> void mergeSort(RandomIt first, RandomIt last) {
    mergeSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void mergeSort(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    if (last - first < 2) return;
    if (last - first == 2) {
        if (comp(*--last, *first)) swap(*first, *last);
    } else {
        auto middle = first + (last - first) / 2;
        mergeSort(first, middle, comp);
        mergeSort(middle, last, comp);
        detail::merge(first, middle, last, comp);
    }
}

/* Heap sort
 * best: O(nlgn); average: O(nlgn); worst: O(nlgn)
 */
namespace detail {
    // return last if pos has no children
    template <std::size_t D, class RandomIt>
    constexpr RandomIt firstChild(RandomIt first, RandomIt last, RandomIt pos) {
        return (first + (pos - first) * D + 1 < last) ? (first + (pos - first) * D + 1) : last;
    }
    // return past-the-last child
    template <std::size_t D, class RandomIt>
    constexpr RandomIt lastChild(RandomIt first, RandomIt last, RandomIt pos) {
        return (firstChild<D>(first, last, pos) + D < last)
                   ? (firstChild<D>(first, last, pos) + D)
                   : last;
    }
    // trying to get parent of root is undefined behaviour
    template <std::size_t D, class RandomIt>
    constexpr RandomIt parent(RandomIt first, RandomIt pos) {
        return first + (pos - first - 1) / D;
    }

    template <std::size_t D, class RandomIt, class Compare>
    void maxHeapify(RandomIt first, RandomIt last, RandomIt pos, Compare comp) {
        using std::swap;
        while (true) {
            auto largest = pos;
            for (auto child = firstChild<D>(first, last, pos);
                 child != lastChild<D>(first, last, pos); ++child) {
                if (comp(*largest, *child)) largest = child;
            }
            if (largest == pos) break;
            swap(*pos, *largest);
            pos = largest;
        }
    }

    template <std::size_t D, class RandomIt, class Compare>
    void buildMaxHeap(RandomIt first, RandomIt last, Compare comp) {
        if (last - first < 2) return;
        for (auto p = parent<D>(first, last - 1); p - first >= 0; --p)
            maxHeapify<D>(first, last, p, comp);
    }
} // namespace detail

template <class RandomIt> void heapSort(RandomIt first, RandomIt last) {
    heapSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    detail::buildMaxHeap<2>(first, last, comp);
    while (last - first > 1) {
        swap(*first, *--last);
        detail::maxHeapify<2>(first, last, first, comp);
    }
}