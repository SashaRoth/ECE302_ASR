#include "limited_size_bag.hpp"

template <typename T>
LimitedSizeBag<T>::LimitedSizeBag()
{
  current_size = 0;
}

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

template <typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if (current_size == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
uint32_t LimitedSizeBag<T>::getCurrentSize() const
{
  return current_size;
}

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

template <typename T>
void LimitedSizeBag<T>::clear()
{
  for (uint8_t i = 0; i < current_size; i++)
  {
    items[i] = T(); // Reset to default value
  }
  current_size = 0; // Reset size
}

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