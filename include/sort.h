#ifndef SORTING_H
#define SORTING_H

/* all the sorting algorithm needs random access iterators, and
 * the type the iterator references to should be swappable,
 * use operator< to compare elements by default
 */

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

// heap sort
template <class RandomIt> void heapSorting(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void heapSorting(RandomIt first, RandomIt last, Compare comp);

#include "sort.hpp"

#endif