#include "priority_queue.hpp"
#include "sorted_list.hpp"

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
}

template <typename T>
void PriorityQueue<T>::remove()
{
    priority_list.removeAt(priority_list.getLength() - 1);
}

template <typename T>
T PriorityQueue<T>::peek()
{
    T result = priority_list.getEntry(priority_list.getLength() - 1);
    return result;
}