#ifndef LIMITED_SIZE_BAG_HPP
#define LIMITED_SIZE_BAG_HPP

#include "abstract_bag.hpp"

template <typename T>
class LimitedSizeBag : public AbstractBag<T>
{
public:
  /**
   * Default constructor initializing an empty bag
   */
  LimitedSizeBag();

  /**
   * Add an item to the bag
   * @param item item to add
   * @return true if item was added, false if bag is full
   */
  bool add(const T &item);

  /**
   * Remove an item from the bag
   * @param item item to remove
   * @return true if item was removed, false if not found
   */
  bool remove(const T &item);

  /**
   * Check if the bag is empty
   * @return true if bag is empty, false if not
   */
  bool isEmpty() const;

  /**
   * Get the current number of items in the bag
   * @return number of items in the bag
   */
  int getCurrentSize() const;

  /**
   * Clear the bag contents
   */
  void clear();

  /**
   * Get the frequency of an item in the bag
   * @param item item to count
   * @return number of times item occurs in the bag
   */
  int getFrequencyOf(const T &item) const;

  /**
   * Check if the bag contains a certain item
   * @param item item to check for
   * @return true if item is in the bag, false if not
   */
  bool contains(const T &item) const;

  /**
   * Check if two bags are equal
   * @param other other bag to compare with
   * @return true if bags are equal, false if not
   */
  bool operator==(const AbstractBag<T> &other) const;

  // static variable to store the limited size
  static const int maxsize = 100;

private:
  T items[maxsize];
  int current_size;
};

#include "limited_size_bag.tpp"
#endif