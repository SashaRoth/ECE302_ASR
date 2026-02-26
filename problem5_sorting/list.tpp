#include "list.hpp"

template <typename T>
List<T>::List()
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
List<T>::~List()
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
List<T>::List(const List<T> &x)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return *this;
}

template <typename T>
void List<T>::swap(List &x)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return true;
}

template <typename T>
int List<T>::getLength() const noexcept
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return 0;
}

template <typename T>
bool List<T>::insert(int position, const T &item)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return true;
}

template <typename T>
bool List<T>::remove(int position)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return true;
}

template <typename T>
void List<T>::clear()
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
T List<T>::getEntry(int position) const
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
  return T();
}

template <typename T>
void List<T>::setEntry(int position, const T &newValue)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}

template <typename T>
void List<T>::moveEntry(int from, int to)
{
  // TODO, feel free to reuse your Problem 3 code, note the 1-index based list
}