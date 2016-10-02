#include <vector>

namespace detail {
    // main KMP algorithm
    // return number of matches if times == 0
    // return the index in main where the times_th match begins
    template <class RandomIt>
    std::size_t KMP_impl(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
                         RandomIt patternLast, std::size_t times);

    template <class RandomIt> std::vector<int> getNext(RandomIt first, RandomIt last);
} // namespace  detail

template <class RandomIt>
std::size_t KMP(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
                RandomIt patternLast) {
    return detail::KMP_impl(mainFirst, mainLast, patternFirst, patternLast, 0);
}

template <class RandomIt>
RandomIt KMP(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
             RandomIt patternLast, std::size_t xth) {
    return xth == 0 ? mainLast : mainFirst + detail::KMP_impl(mainFirst, mainLast,
                                                              patternFirst, patternLast, xth);
}

namespace detail {
    template <class RandomIt>
    std::size_t KMP_impl(RandomIt mainFirst, RandomIt mainLast, RandomIt patternFirst,
                         RandomIt patternLast, std::size_t times) {
        std::size_t counts = 0;
        auto next = getNext(patternFirst, patternLast);
        auto i = 0, j = 0;
        while (i < mainLast - mainFirst) {
            if (j == -1 || mainFirst[i] == patternFirst[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
            if (j == patternLast - patternFirst) {
                if (++counts == times) return i - j;
                j = next[j];
            }
        }
        // return index of mainLast if no match or times of match less than required
        return times == 0 ? counts : static_cast<std::size_t>(i);
    }

    template <class RandomIt> std::vector<int> getNext(RandomIt first, RandomIt last) {
        std::vector<int> next(last - first + 1, 0);
        next[0] = -1;
        auto i = 0, j = -1;
        while (i < last - first) {
            if (j == -1 || first[i] == first[j]) {
                ++i;
                ++j;
                if (first[i] == first[j])
                    next[i] = next[j];
                else
                    next[i] = j;
            } else
                j = next[j];
        }
        next[i] = j;
        return next;
    }
} // namespace  detail