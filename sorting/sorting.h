#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>

class Sorting {
  public:
    using data_type = int;
    Sorting() = default;
    Sorting(std::initializer_list<data_type> li) : data_(li) {}
    void push_back(data_type const &i) { data_.push_back(i); }
    void push_back(data_type &&i) { data_.push_back(std::move(i)); }
    void insertSorting();
    void selectSorting();
    void bubbleSorting();

    friend std::ostream &operator<<(std::ostream &os, Sorting const &s) {
        for (auto i : s.data_) os << i << '\t';
        return os;
    }

  private:
    std::vector<data_type> data_;
};

#endif