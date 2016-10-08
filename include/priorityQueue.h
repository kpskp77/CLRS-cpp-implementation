#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <vector>

template <class Key> class MaxPriorityQueue;

template <class Key> std::ostream &operator<<(std::ostream &, MaxPriorityQueue<Key> const &);

template <class Key> class MaxPriorityQueue {
    friend std::ostream &operator<<<Key>(std::ostream &, MaxPriorityQueue<Key> const &);

  public:
    // user should make sure this queue is not empty
    Key max() const { return data_[0]; }
    Key extractMax();

    void insert(Key key);

    // user should make sure newKey is larger than index_th key
    void increaseKey(std::size_t index, Key newKey);

    bool empty() const { return data_.empty(); }

  private:
    std::vector<Key> data_;
};

#include "priorityQueue.hpp"

#endif