#ifndef _DYNAMIC_BAG_HPP_
#define _DYNAMIC_BAG_HPP_

#include "abstract_bag.hpp"

template <typename T>
class DynamicBag : public AbstractBag<T>
{
public:
  // default constructor
  DynamicBag();

  // copy constructor
  DynamicBag(const DynamicBag &x);

  // destructor
  ~DynamicBag() override;

  // copy assignment
  DynamicBag &operator=(DynamicBag x);

  // swap for copy swap idiom
  void swap(DynamicBag &x);

  // add an item to the bag
  bool add(const T &item) override;

  // remove an item
  bool remove(const T &item) override;

  // check is the bag is empty
  bool isEmpty() const override;

  // get number of items in the bag
  uint32_t getCurrentSize() const override;

  // clear the bag contents
  void clear() override;

  // count how many time item occurs in bag
  uint32_t getFrequencyOf(const T &item) const override;

  // check if item is in the bag
  bool contains(const T &item) const override;

  // check if two bags are equal
  bool operator==(const AbstractBag<T> &other) const override;

private:
  uint32_t current_size;
  T *data = new T[0];
};

#include "dynamic_bag.tpp"
#endif