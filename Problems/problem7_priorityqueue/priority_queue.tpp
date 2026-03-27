#include "priority_queue.hpp"
#include "sorted_list.hpp"
#include <iostream>

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    if (priority_list.getLength() == 0) {return true;}
    return false;
}

template <typename T>
void PriorityQueue<T>::add(const T &item)
{
    priority_list.insert(item);
    //std::cout << "Current length after add: " << priority_list.getLength() << std::endl;
}

template <typename T>
void PriorityQueue<T>::remove()
{
    priority_list.removeAt(priority_list.getLength());
    //std::cout << "Current length after remove: " << priority_list.getLength() << std::endl;
}

template <typename T>
T PriorityQueue<T>::peek()
{
    T result = priority_list.getEntry(priority_list.getLength());
    return result;
}