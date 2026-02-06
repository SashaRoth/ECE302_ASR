#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  size = 0;
  headptr = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  // TODO, destructor
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  size = 0;
  headptr = nullptr;

  if(x.getLength == 0){
    return; //list is empty, noting to copy
  }

  headptr = new Node(x.headptr->getItem());
  size++;

  Node *current_ptr = headptr; 
  Node *x_next_ptr = x.headptr->getNext();

  while(x_next_ptr != nullptr){
    current_ptr->setNext(new Node(x_next_ptr->data)); //a little convoluted but it might work?
    current_ptr = current_ptr->getNext();
    x_next_ptr = x_next_ptr->getNext();
    size++;
  }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  Node *temp_ptr = headptr;
  temp_ptr = x.headptr;
  x.headptr = temp_ptr;

  int temp_size = size;
  size = x.size;
  x.size = temp_size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  // TODO
  return true;
}

template <typename T>
int LinkedList<T>::getLength() const noexcept
{
  // TODO
  return 0;
}

template <typename T>
bool LinkedList<T>::insert(int position, const T &item)
{
  // TODO
  return true;
}

template <typename T>
bool LinkedList<T>::remove(int position)
{
  // TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  // TODO
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T LinkedList<T>::getEntry(int position) const
{
  // TODO
  return T();
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void LinkedList<T>::setEntry(int position, const T &newValue)
{
  // TODO
}
