#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  current_size = 0;
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  // TODO
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  // TODO
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  // TODO, use copy swap idiom
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  // TODO
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  data[current_size] = item;
  current_size++;
  return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  bool flag = false;
  T *newdata = new T[current_size - 1];
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item)
    {
      flag = true;
    }
    else
    {
      newdata[i] = data[i + (flag ? 1 : 0)];
    }
  }
  if (flag)
  {
    current_size--;
    delete[] data;
    data = newdata;
    return true;
  }
  else
  {
    delete[] newdata;
    return false;
  }
}

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  if (current_size == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
uint32_t DynamicBag<T>::getCurrentSize() const
{
  return current_size;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
{
  // TODO
  return false;
}

template <typename T>
void DynamicBag<T>::clear()
{
  // TODO
}

template <typename T>
int DynamicBag<T>::getFrequencyOf(const T &item) const
{
  // TODO
  return 0;
};

template <typename T>
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
{
  // TODO
  return false;
}