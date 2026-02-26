#ifndef _SORT_HPP
#define _SORT_HPP

#include "list.hpp"

/** Sorts an array into ascending order. Uses the quick sort method.
 @pre  list[first..last] is an array.
 @post  list[first..last] is sorted.
 @throw std::out_of_range if first < 1 or last > list.getLength(), 1-based indexing is used.
 @param list The given array.
 @param first The start element to consider in list.
 @param last The end element to consider in list. */
template <typename T>
void quick_sort(List<T> &list, int first, int last)
{
    // TODO
    // Must call helper function partition()
}

/** Partitions the entries in an array about a pivot entry for quicksort.
 @pre  list[first..last] is an array; first <= last.
 @throw std::out_of_range if first > last, or if first < 1 or last > list.getLength()
 @post  list[first..last] is partitioned such that:
        S1 = list[first..pivotIndex-1] <= pivot
             list[pivotIndex]          == pivot
        S2 = list[pivotIndex+1..last]  >= pivot
 @param list The given array.
 @param first The start entry to consider in list.
 @param last The end entry to consider in list.
 @return The index of the pivot. */
template <typename T>
int partition(List<T> &list, int first, int last)
{
    // TODO
    // You can choose the pivot yourself, but no matter what you choose
    // list[first..pivotIndex-1] <= pivot, list[pivotIndex] == pivot, list[pivotIndex + 1..last] >= pivot
}
#endif