#ifndef _DYNAMIC_BAG_HPP_
#define _DYNAMIC_BAG_HPP_

#include "abstract_bag.hpp"

template <typename T>
class DynamicBag : public AbstractBag<T>
{
public:
  /**
   * Default constructor initializing an empty bag
   */
  DynamicBag();

  /**
   * Copy constructor for deep copy
   * @param x DynamicBag to copy from
   */
  DynamicBag(const DynamicBag &x);

  /**
   * Destructor to free allocated memory
   */
  ~DynamicBag() override;

  /**
   * Copy assignment operator using copy-and-swap idiom
   * @param x DynamicBag to copy from
   * @return reference to *this DynamicBag, now with new contents
   */
  DynamicBag &operator=(DynamicBag x);

  /**
   * Swap method for copy-and-swap idiom
   * @param x DynamicBag to swap contents with
   */
  void swap(DynamicBag &x);

  /**
   * Add an item to the bag
   * @param item item to add
   * @return true if added successfully, false if capacity exceeded
   */
  bool add(const T &item) override;

  /**
   * Remove an item from the bag
   * @param item item to remove
   * @return true if removed successfully, false if not found
   */
  bool remove(const T &item) override;

  /**
   * Check if the bag is empty
   * @return true if bag is empty, false if not
   */
  bool isEmpty() const override;

  /**
   * Get the current size of the bag
   * @return current size of the bag
   */
  uint32_t getCurrentSize() const override;

  /**
   * Clear the bag contents
   */
  void clear() override;

  /**
   * Get the frequency of an item in the bag
   * @param item item to count
   * @return frequency of the item in the bag
   */
  uint32_t getFrequencyOf(const T &item) const override;

  /**
   * Check if the bag contains a certain item
   * @param item item to check for
   * @return true if item is in the bag, false if not
   */
  bool contains(const T &item) const override;

  /**
   * Check if two bags are equal
   * @param other other bag to compare with
   * @return true if bags are equal, false if not
   */
  bool operator==(const AbstractBag<T> &other) const override;

private:
  uint32_t current_size;
  T *data = new T[0];
};

#include "dynamic_bag.tpp"
#endif