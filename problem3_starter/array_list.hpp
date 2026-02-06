#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "abstract_list.hpp"

template <typename T>
class ArrayList : public AbstractList<T>
{
public:
  /**
   * default constructor
   */
  ArrayList();

  /**
   * destructor
   */
  ~ArrayList();

  /**
   * copy constructor
   * @param rhs the ArrayList to copy
   */
  ArrayList(const ArrayList &rhs);

  /**
   * copy assignment operator
   * @param rhs the ArrayList to copy
   * @return a reference to the copied ArrayList
   */
  ArrayList &operator=(ArrayList rhs);

  /**
   * swap method to use in copy assignment operator
   * @param rhs the ArrayList to swap with the current ArrayList
   */
  void swap(ArrayList &rhs);

  /**
   * determine if a list is empty
   * @return true if the list is empty, false otherwise
   */
  bool isEmpty() const noexcept;

  /**
   * return current length of the list
   * @return the current length of the list
   */
  int getLength() const noexcept;

  /**
   * insert item at position in the list
   * @param position the position to insert the item at (1-based indexing)
   * @param item the item to insert
   * @return true if the item was successfully inserted, false if the position is invalid
   */
  bool insert(int position, const T &item);

  /**
   * remove item at position in the list
   * @param position the position to remove the item from (1-based indexing)
   * @return true if the item was successfully removed, false if the position is invalid
   */
  bool remove(int position);

  /**
   * remove all items from the list
   */
  void clear();

  /**
   * retrieve the value of the item at position
   * @param position the position to retrieve the item from (1-based indexing)
   * @return a copy of the item at position
   * @throws std::out_of_range if position < 1 or position > getLength
   */
  T getEntry(int position) const;

  /**
   * set the value of the item at position
   * @param position the position to set the item at (1-based indexing)
   * @param newValue the new value to set at position
   * @throws std::out_of_range if position < 1 or position > getLength
   */
  void setEntry(int position, const T &newValue);

private:
  int size;      // current number of elements in the list
  T *data;      // dynamic array to hold list elements
};

#include "array_list.tpp"

#endif