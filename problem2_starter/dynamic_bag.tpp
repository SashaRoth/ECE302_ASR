#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  data = new T[0];
  current_size = 0;
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T> &x)
{
  current_size = x.getCurrentSize(); // copy size
  data = new T[current_size];        // allocate new array with other array's size
  for (uint32_t i = 0; i < x.current_size; i++)
  {
    data[i] = x.data[i]; // copy data from other array
  }
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  delete[] data;  // free allocated memory
  data = nullptr; // avoid dangling pointer
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x) // passed by value, copy constructed
{
  swap(x);      // swap current object with copy
  return *this; // return current object by reference, copy is destroyed
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  T temp_data = data;                // create temporary data pointer
  uint32_t temp_size = current_size; // create temporary size

  temp_size = x.current_size; // copy other size to temp
  temp_data = x.data;         // copy other data to temp

  x.data = data;                 // swap data pointers
  x.current_size = current_size; // swap sizes

  data = temp_data;         // assign temp data to *this
  current_size = temp_size; // assign temp size to *this

  delete[] temp_data;  // free temporary data
  temp_data = nullptr; // avoid dangling pointer
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  T *newdata = new T[current_size + 1]; // allocate new array with one extra space
  for (uint32_t i = 0; i < current_size; i++)
  {
    newdata[i] = data[i]; // copy old data to new array
  }
  data[current_size] = item; // add new item at the end
  delete[] data;             // free old array
  data = newdata;            // point to new array
  current_size++;
  return true;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  bool flag = false;                    // to check if item is found
  T *newdata = new T[current_size - 1]; // allocate new array with one less space
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item) // if item is found
    {
      flag = true;
    }
    else
    {
      newdata[i] = data[i + (flag ? 1 : 0)]; // copy old data to new array, skip the found item
    }
  }
  if (flag) // if item was found and removed
  {
    current_size--;
    delete[] data;     // free old array
    data = newdata;    // point to new array
    delete[] newdata;  // free temporary array
    newdata = nullptr; // avoid dangling pointer
    return true;
  }
  else // if item was not found
  {
    delete[] newdata;  // free temporary array
    newdata = nullptr; // avoid dangling pointer
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
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item) // if item is found
    {
      return true;
    }
  }
  return false;
}

template <typename T>
void DynamicBag<T>::clear()
{
  delete[] data;    // free old array
  data = new T[0];  // allocate new empty array
  current_size = 0; // reset size to zero
}

template <typename T>
int DynamicBag<T>::getFrequencyOf(const T &item) const
{
  int count = 0; // initialize count to zero
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item)
    {
      count++; // increment count if item matches
    }
  }
  return count;
};

template <typename T>
bool DynamicBag<T>::operator==(const AbstractBag<T> &other) const
{
  if (current_size != other.getCurrentSize()) // check size first
  {
    return false;
  }
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (this->getFrequencyOf(data[i]) != other.getFrequencyOf(data[i])) // check frequency of each item
    {
      return false;
    }
  }
  return true;
}