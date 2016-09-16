#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>

class Sorting {
  public:
    using element_type = int;
    using data_type = std::vector<element_type>;
    using iterator = data_type::iterator;
    Sorting() = default;
    Sorting(std::initializer_list<element_type> li) : data_(li) {}

    void push_back(element_type const &i) { data_.push_back(i); }
    void push_back(element_type &&i) { data_.push_back(std::move(i)); }

    void insertSorting() { insertSorting(data_.begin(), data_.end()); }
    void selectSorting() { selectSorting(data_.begin(), data_.end()); }
    void bubbleSorting() { bubbleSorting(data_.begin(), data_.end()); }
    void mergeSorting() { mergeSorting(data_.begin(), data_.end()); }

    friend std::ostream &operator<<(std::ostream &os, Sorting const &s) {
        for (auto i : s.data_) os << i << '\t';
        return os;
    }

  private:
    data_type data_;

    // sorting algorithms
    void insertSorting(iterator, iterator);
    void selectSorting(iterator, iterator);
    void bubbleSorting(iterator, iterator);
    void mergeSorting(iterator, iterator);

    // helper functions
    void merge(iterator, iterator, iterator);
    bool isSorted(iterator, iterator);
};

#endif