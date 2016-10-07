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
    template <class RandomIt, class Compare>
    void maxHeapify(RandomIt first, RandomIt last, int index, Compare comp) {
        using std::swap;
        /* recursion version
        if (index > (last - first) / 2) return;
        auto left = 2 * index;
        auto right = 2 * index + 1;
        auto largest = index;
        if (comp(first[largest - 1], first[left - 1])) largest = left;
        if (right <= last - first && comp(first[largest - 1], first[right - 1]))
            largest = right;
        if (largest != index) {
            swap(first[index - 1], first[largest - 1]);
            maxHeapify(first, last, largest, comp);
        }
        // end recursion version */
        //* iteration version
        decltype(index) left, right, largest;
        while (index <= (last - first) / 2) {
            left = 2 * index;
            right = 2 * index + 1;
            largest = index;
            if (comp(first[largest - 1], first[left - 1])) largest = left;
            if (right <= last - first && comp(first[largest - 1], first[right - 1]))
                largest = right;
            if (largest == index) break;
            swap(first[index - 1], first[largest - 1]);
            index = largest;
        }
        // end iteration version */
    }

    template <class RandomIt, class Compare>
    void buildMaxHeap(RandomIt first, RandomIt last, Compare comp) {
        for (auto i = (last - first) / 2; i > 0; --i) maxHeapify(first, last, i, comp);
    }
} // namespace detail

template <class RandomIt> void heapSort(RandomIt first, RandomIt last) {
    heapSort(first, last, detail::less);
}

template <class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp) {
    using std::swap;
    detail::buildMaxHeap(first, last, comp);
    while (last - first > 1) {
        swap(*first, *--last);
        detail::maxHeapify(first, last, 1, comp);
    }
}