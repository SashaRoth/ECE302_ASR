#ifndef _PRIORITY_QUEUE_HPP_
#define _PRIORITY_QUEUE_HPP_

#include "abstract_priority_queue.hpp"
#include "sorted_list.hpp"

// Type T must be orderable
template <typename T>
class PriorityQueue : public AbstractPriorityQueue<T>
{
public:
  bool isEmpty() const;

  void add(const T &item);

  /** Remove the item with the highest priority from the queue
   * @throw std::out_of_range if queue is empty */
  void remove();

  /** @return the item with the highest priority from the queue
   * @throw std::out_of_range if queue is empty */
  T peek();

private:
  SortedList<T> priority_list; //has-a relationship between PriorityQueue and SortedList
  //size variable not needed, can use SortedList's getLength method
};

#include "priority_queue.tpp"

#endif