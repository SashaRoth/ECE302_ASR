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
  clear();
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
  if(size == 0){
    return true;
  }
  return false;
}

template <typename T>
int LinkedList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
bool LinkedList<T>::insert(int position, const T &item) //returns false if invalid index
{
  if(position < 1 || position > size + 1){
    return false; //position is out of bounds
  }
  Node *current = headptr;
  Node *new_node = new Node(item); //create new node with item as data
  for(int i = 1; i < position - 1; i++){ //iteratire through list until position - 1
    current = current->getNext();
  }
  new_node->setNext(current->getNext()); //set next node of new pointer to the next node of current
  current->setNext(new_node); //set next node of current to new pointer
  size++; //increment size
  return true;
}

template <typename T>
bool LinkedList<T>::remove(int position) //returns false if invalid index
{
  if(position < 1 || position > size){
    return false; //position is out of bounds
  }

  Node *prev = headptr;
  Node *to_remove = nullptr;
  Node *next = nullptr;

  for(int i = 1; i < position - 1; i++){ //iterate through list until node before one to be removed
    prev = prev->getNext();
  }

  to_remove = prev->getNext(); //store pointer to node to be removed
  next = to_remove->getNext(); //store pointer to node after node to be removed
  prev->setNext(next); //set next node of current to node after node to be removed
  
  to_remove->setNext(nullptr); //set next node of node to be removed to nullptr
  delete to_remove; //delete node to be removed
  
  size--; //decrement size
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  Node* current = headptr;
  Node* next = nullptr;
  while(current != nullptr){
    next = current->getNext();
    delete current;
    current = next;
  }
  headptr = nullptr;
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T LinkedList<T>::getEntry(int position) const //throws std::out_of_range if position is invalid
{
  if(position < 1 || position > size){
    throw std::out_of_range("Invalid index");
  }

  Node *current = headptr;
  for(int i = 1; i < position; i++){ //iterate through list until position
    current = current->getNext();
  }
  return current->getItem(); //return item at position
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void LinkedList<T>::setEntry(int position, const T &newValue) //throws std::out_of_range if position is invalid
{
  if(position < 1 || position > size){
    throw std::out_of_range("Invalid index");
  }
  Node *current = headptr;
  for(int i = 1; i < position; i++){ //iterate through list until position
    current = current->getNext();
  }
  current->setItem(newValue); //return item at position
}
