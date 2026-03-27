#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include "abstract_list.hpp"
#include "Node.hpp"

template <typename T>
class LinkedList : public AbstractList<T>
{
public:
  /**
   * default constructor
   */
  LinkedList();

  /**
   * copy constructor
   * @param x the LinkedList to copy
   */
  LinkedList(const LinkedList &x);

  /**
   * destructor
   */
  ~LinkedList();

  /**
   * copy assignment operator
   * @param x the LinkedList to copy
   * @return a reference to the copied LinkedList
   */
  LinkedList &operator=(LinkedList x);

  /**
   * swap method to use in copy assignment operator
   * @param x the LinkedList to swap with the current LinkedList
   */
  void swap(LinkedList &x);

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
  int size;
  Node<T> *headptr;
};

#include "linked_list.tpp"

#endif