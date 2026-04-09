#include "queue.hpp"

template <typename T>
bool Queue<T>::isEmpty() const
{
  return internal_list.isEmpty();
}

template <typename T>
void Queue<T>::enqueue(const T &item)
{
  internal_list.insert(internal_list.getLength(), item);
  return;
}

template <typename T>
void Queue<T>::dequeue()
{
  internal_list.remove(0);
  return;
}

template <typename T>
T Queue<T>::peekFront() const
{
  return internal_list.getEntry(0);
}