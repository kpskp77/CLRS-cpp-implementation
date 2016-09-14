#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>

class Sorting {
  public:
    using data_type = int;
    using iterator = std::vector<data_type>::iterator;
    Sorting() = default;
    Sorting(std::initializer_list<data_type> li) : data_(li) {}

    void push_back(data_type const &i) { data_.push_back(i); }
    void push_back(data_type &&i) { data_.push_back(std::move(i)); }

    void insertSorting() { insertSorting(data_.begin(), data_.end()); }
    void selectSorting() { selectSorting(data_.begin(), data_.end()); }
    void bubbleSorting() { bubbleSorting(data_.begin(), data_.end()); }

    friend std::ostream &operator<<(std::ostream &os, Sorting const &s) {
        for (auto i : s.data_) os << i << '\t';
        return os;
    }

  private:
    std::vector<data_type> data_;

    void insertSorting(iterator, iterator);
    void selectSorting(iterator, iterator);
    void bubbleSorting(iterator, iterator);
};

#endif