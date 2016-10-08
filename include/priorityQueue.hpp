#include "sort.h"

template <class Key> void MaxPriorityQueue<Key>::insert(Key key) {
    data_.push_back(key);
    increaseKey(data_.size() - 1, key);
}

template <class Key> Key MaxPriorityQueue<Key>::extractMax() {
    auto key = data_[0];
    data_[0] = data_.back();
    data_.pop_back();
    detail::maxHeapify(data_.begin(), data_.end(), 1, detail::less);
    return key;
}

template <class Key> void MaxPriorityQueue<Key>::increaseKey(std::size_t index, Key newKey) {
    using std::swap;
    data_[index] = newKey;
    while (index > 0) {
        auto parent = (index - 1) / 2;
        if (!(data_[parent] < data_[index])) break;
        swap(data_[parent], data_[index]);
        index = parent;
    }
}

template <class Key>
inline std::ostream &operator<<(std::ostream &os, MaxPriorityQueue<Key> const &maxQueue) {
    for (auto i = 1; i <= maxQueue.data_.size() / 2; ++i) {
        os << maxQueue.data_[i - 1] << ' ' << maxQueue.data_[2 * i - 1] << ' ';
        if (2 * i <= maxQueue.data_.size() - 1) os << maxQueue.data_[2 * i];
        os << '\n';
    }
    return os;
}