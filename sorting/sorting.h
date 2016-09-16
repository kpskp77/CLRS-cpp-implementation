#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>

class Test;

class Sorting {
  public:
    using element_type = int;
    using data_type = std::vector<element_type>;
    using iterator = data_type::iterator;
    using size_type = data_type::size_type;
    Sorting() = default;
    Sorting(std::initializer_list<element_type> li) : data_(li) {}

    void push_back(element_type const &i) { data_.push_back(i); }
    void push_back(element_type &&i) { data_.push_back(std::move(i)); }
    void reserve(size_type capicity) { data_.reserve(capicity); }

    void insertSorting() { insertSorting(data_.begin(), data_.end()); }
    void selectSorting() { selectSorting(data_.begin(), data_.end()); }
    void bubbleSorting() { bubbleSorting(data_.begin(), data_.end()); }
    void mergeSorting() { mergeSorting(data_.begin(), data_.end()); }

    friend std::ostream &operator<<(std::ostream &, Sorting const &);

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

class Test {
  public:
    Test(int i) : i(new int(i)) {}
    Test(Test const &t) : i(new int(*t.i)) { std::cout << "Test(Test const &)\n"; }
    Test(Test &&t) noexcept : i(t.i) {
        t.i = nullptr;
        std::cout << "Test(Test &&)\n";
    }
    ~Test() noexcept { delete i; }
    Test &operator=(Test const &t) {
        *i = *t.i;
        return *this;
    }
    Test &operator=(Test &&t) noexcept {
        i = t.i;
        t.i = nullptr;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, Test const &t) {
        os << *t.i;
        return os;
    }
    friend bool operator>(Test const &t1, Test const &t2) { return *t1.i > *t2.i; }

  private:
    int *i;
};

inline std::ostream &operator<<(std::ostream &os, Sorting const &s) {
    for (auto const &i : s.data_) os << i << '\t';
    return os;
}

#endif