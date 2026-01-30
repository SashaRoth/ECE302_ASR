#include "limited_size_bag.hpp"

/**
 * Default constructor initializing an empty bag
 */
template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
  current_size = 0;
}

/**
 * Add an item to the bag
 * @param item item to add
 * @return true if item was added, false if bag is full
 */
template <typename T>
bool LimitedSizeBag<T>::add(const T &item)
{
  if (current_size < maxsize)
  {
    items[current_size] = item;
    current_size++;
    return true;
  }
  return false;
}

/**
 * Remove an item from the bag
 * @param item item to remove
 * @return true if item was removed, false if not found
 */
template <typename T>
bool LimitedSizeBag<T>::remove(const T &item)
{
  bool found = false;
  for (uint8_t i = 0; i < current_size; i++)
  {
    if (items[i] == item) // Check for first match
    {
      found = true;
      current_size--;
    }
    if (found)
    {
      items[i] = items[i + 1]; // Shift items down, overwriting removed item
    }
  }
  return found;
}

/**
 * Check if the bag is empty
 * @return true if bag is empty, false if not
 */
template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
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
uint32_t LimitedSizeBag<T>::getCurrentSize() const
{
  return current_size;
}

/**
 * Check if the bag contains a certain item
 * @param item item to check for
 * @return true if item is in the bag, false if not
 */
template <typename T>
bool LimitedSizeBag<T>::contains(const T &item) const
{
  for (uint8_t i = 0; i < current_size; i++)
  {
    if (items[i] == item) // Check for match
    {
      return true; // Item found
    }
  }
  return false;
}

/**
 * Clear the bag contents
 */
template <typename T>
void LimitedSizeBag<T>::clear()
{
  for (uint8_t i = 0; i < current_size; i++)
  {
    items[i] = T(); // Reset to default value
  }
  current_size = 0; // Reset size
}

/**
 * Get the frequency of an item in the bag
 * @param item item to count
 * @return number of times item occurs in the bag
 */
template <typename T>
uint32_t LimitedSizeBag<T>::getFrequencyOf(const T &item) const
{
  uint32_t count = 0;
  for (uint8_t i = 0; i < current_size; i++)
  {
    if (items[i] == item) // Check for match
    {
      count++; // Increment count
    }
  }
  return count;
};

/**
 * Check if two bags are equal
 * @param other other bag to compare with
 * @return true if bags are equal, false if not
 */
template <typename T>
bool LimitedSizeBag<T>::operator==(const AbstractBag<T> &other) const
{
  if (current_size != other.getCurrentSize()) // Compare sizes
  {
    return false;
  }
  for (uint8_t i = 0; i < current_size; i++)
  {
    if (this->getFrequencyOf(items[i]) != other.getFrequencyOf(items[i])) // Compare amounts of each item
    {
      return false;
    }
  }
  return true;
}