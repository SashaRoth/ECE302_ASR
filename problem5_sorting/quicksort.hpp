#ifndef _SORT_HPP
#define _SORT_HPP

#include <iostream>
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
    if(first < 1 || last < 1 || first > last || last > list.getLength()){
        throw std::out_of_range("Invalid bounds indexing quick_sort");
    }
    if(first == last){ //list size of 1; base case
        return;
    }
    int pivot = partition(list, first, last);
    if(pivot > first){ //sort left half if pivot is not at the start
        quick_sort(list, first, pivot - 1);
    }
    if(pivot < last){ //sort right half if pivot is not at the end
        quick_sort(list, pivot + 1, last);
    }

    std::cout << "Current sublist: ";

    for(int i = first; i <= last; i++){
        std::cout << list.getEntry(i) << " ";
    }
    std::cout << std::endl;
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
    int length = list.getLength();
    T pivot_val = list.getEntry(first); //first entry is pivot
    int pivot_index = first; //store initial index of pivot
    if(first > last || first < 1 || last > length){ //check validity of bounds
        throw std::out_of_range("Invalid list bounds partition");
    }
    
    for(int i = first + 1; i <= last; i++){ //start iteration after pivot, i is 1-indexed
        if(list.getEntry(i) >= pivot_val){ //check if current entry is greater than/less than pivot, move accordingly
            list.moveEntry(i, pivot_index + 1); //move greater values to after pivot
        }
        else{
            list.moveEntry(i, pivot_index); //move smaller values to before pivot
            pivot_index++; //increment pivot
        }
    }
    // TODO
    // You can choose the pivot yourself, but no matter what you choose
    // list[first..pivotIndex-1] <= pivot, list[pivotIndex] == pivot, list[pivotIndex + 1..last] >= pivot
    return pivot_index;
}
#endif