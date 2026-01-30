#include "dynamic_bag.hpp"

/**
 * Default constructor initializing an empty bag
 */
template <typename T>
DynamicBag<T>::DynamicBag()
{
  current_size = 0;
}

/**
 * Copy constructor for deep copy
 * @param x DynamicBag to copy from
 */
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

/**
 * Destructor to free allocated memory
 */
template <typename T>
DynamicBag<T>::~DynamicBag()
{
  delete[] data;  // free allocated memory
  data = nullptr; // avoid dangling pointer
}

/**
 * Copy assignment operator using copy-and-swap idiom
 * @param x DynamicBag to copy from
 * @return reference to *this DynamicBag, now with new contents
 */
template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x) // passed by value, copy constructed
{
  swap(x);      // swap current object with copy
  return *this; // return current object by reference, copy is destroyed
}

/* CITATION:
In dynamic_bag.tpp, I encountered several memory leakage errors and improper indexing
on my first attempt. I used the built-in VSCode Github Copilot AI to double-check my add(),
remove(), and swap() methods, and point out where my issues were occuring. The AI suggested copying
the pointers of the dynamic arrays in the swap() method, instead of element by element swapping, which
fixed my issues in that method. I also fixed my add() and remove() methods by properly allocating a
new array, copying the data over, and deleting the old array, which I had previously done in the wrong order.
*/

/**
 * Swap method for copy-and-swap idiom
 * @param x DynamicBag to swap contents with
 */
template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  T *tmp_data = data; // swap data pointers
  data = x.data;
  x.data = tmp_data;

  uint32_t tmp_size = current_size; // swap sizes
  current_size = x.current_size;
  x.current_size = tmp_size;
}

/**
 * Add an item to the bag
 * @param item item to add
 * @return true if added successfully, false if capacity exceeded
 */
template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  T *newdata = new T[current_size + 1]; // allocate new array with one extra space
  for (uint32_t i = 0; i < current_size; i++)
  {
    newdata[i] = data[i]; // copy old data to new array
  }
  newdata[current_size] = item; // add new item at the end
  delete[] data;                // free old array
  data = newdata;               // point to new array
  current_size++;
  return true;
}

/**
 * Remove an item from the bag
 * @param item item to remove
 * @return true if removed successfully, false if not found
 */
template <typename T>
bool DynamicBag<T>::remove(const T &item)
{
  if (current_size == 0)
    return false;

  // find first occurrence
  uint32_t index = -1;
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item)
    {
      index = i; // store index of found object
      break;
    }
  }
  if (index == -1) // item not found
    return false;

  if (current_size == 1)
  {
    // removing the only element
    delete[] data;
    data = new T[0];
    current_size = 0;
    return true;
  }

  T *newdata = new T[current_size - 1]; // allocate new array with one less space
  for (uint32_t i = 0, j = 0; i < current_size; i++)
  {
    if (i == index)
      continue; // skip the item to be removed, skip incrementing j when the index is found
    newdata[j++] = data[i];
  }

  delete[] data;  // free old array
  data = newdata; // point to new array
  current_size--;
  return true;
}

/**
 * Check if the bag is empty
 * @return true if bag is empty, false if not
 */
template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  if (current_size == 0)
  {
    return true;
  }
  return false;
}

/**
 * Get the current size of the bag
 * @return current size of the bag
 */
template <typename T>
uint32_t DynamicBag<T>::getCurrentSize() const
{
  return current_size;
}

/**
 * Check if the bag contains a certain item
 * @param item item to check for
 * @return true if item is in the bag, false if not
 */
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

/**
 * Clear the bag contents
 */
template <typename T>
void DynamicBag<T>::clear()
{
  delete[] data;    // free old array
  data = new T[0];  // allocate new empty array
  current_size = 0; // reset size to zero
}

/**
 * Get the frequency of an item in the bag
 * @param item item to count
 * @return frequency of the item in the bag
 */
template <typename T>
uint32_t DynamicBag<T>::getFrequencyOf(const T &item) const
{
  uint32_t count = 0; // initialize count to zero
  for (uint32_t i = 0; i < current_size; i++)
  {
    if (data[i] == item)
    {
      count++; // increment count if item matches
    }
  }
  return count;
}

/**
 * Check if two bags are equal
 * @param other other bag to compare with
 * @return true if bags are equal, false if not
 */
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