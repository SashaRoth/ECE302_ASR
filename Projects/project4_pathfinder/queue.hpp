#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include "abstract_queue.hpp"

template <typename T>
class Queue : public AbstractQueue<T>
{
public:
  bool isEmpty() const;

  void enqueue(const T &item);

  void dequeue();

  T peekFront() const;

private:
  List<T> internal_list;
};

#include "queue.tpp"

#endif