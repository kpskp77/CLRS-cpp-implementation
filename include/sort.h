#ifndef SORTING_H
#define SORTING_H

/* all the sorting algorithm needs random access iterators, and
 * the type the iterator references to should be swappable,
 * use operator< to compare elements by default
 */

// insert sort
template <class RandomIt> void insertSort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void insertSort(RandomIt first, RandomIt last, Compare comp);

// select sort
template <class RandomIt> void selectSort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void selectSort(RandomIt first, RandomIt last, Compare comp);

// bubble sort
template <class RandomIt> void bubbleSort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void bubbleSort(RandomIt first, RandomIt last, Compare comp);

// merge sort
template <class RandomIt> void mergeSort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void mergeSort(RandomIt first, RandomIt last, Compare comp);

// heap sort
template <class RandomIt> void heapSort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp);

#include "sort.hpp"

#endif