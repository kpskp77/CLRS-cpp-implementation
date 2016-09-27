#ifndef SORTING_H
#define SORTING_H

// insert sort
template <class RandomIt> void insertSorting(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void insertSorting(RandomIt first, RandomIt last, Compare comp);

// select sort
template <class RandomIt> void selectSorting(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void selectSorting(RandomIt first, RandomIt last, Compare comp);

// bubble sort
template <class RandomIt> void bubbleSorting(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void bubbleSorting(RandomIt first, RandomIt last, Compare comp);

// merge sort
template <class RandomIt> void mergeSorting(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void mergeSorting(RandomIt first, RandomIt last, Compare comp);

#include "sorting.hpp"

#endif