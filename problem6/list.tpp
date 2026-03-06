#include "list.hpp"

template <typename T>
List<T>::List()
{
  size = 0;
  data = new T[0]; // initial capacity of 0
}

template <typename T>
List<T>::~List()
{
  delete[] data;
  data = nullptr;
}

template <typename T>
List<T>::List(const List<T> &x)
{
  size = x.getLength(); // copy size
  data = new T[size];        // allocate new list with other list's size
  for (int i = 0; i < x.size; i++)
  {
    data[i] = x.data[i]; // copy data from other list element-by-element
  }
}

template <typename T>
List<T> &List<T>::operator=(List<T> x)
{
  swap(x);      // swap current object with copy
  return *this; // return current object by reference, copy is destroyed
}

template <typename T>
void List<T>::swap(List &x)
{
  T *tmp_data = new T[size];
  tmp_data = data; // swap data pointers
  data = x.data;
  x.data = tmp_data;

  int tmp_size = size; // swap sizes
  size = x.size;
  x.size = tmp_size;
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  std::cout << "size: " << size << std::endl; // debug statement to check size
  if (size == 0){
    return true;
  }
  return false;
}

template <typename T>
int List<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
void List<T>::insert(int position, const T &item)
{
   if(position < 1 || position > size + 1) {
    throw std::out_of_range("Invalid index: insert"); // invalid position
  }

  T *temp = new T[size + 1]; // create new array with increased size
  for(int i = 0; i < size + 1; i++) {
    if(i == position - 1) {
      temp[i] = item; // insert new item at position
    } else if(i > position - 1) {
      temp[i] = data[i - 1]; // shift elements right after position
    } else{
    temp[i] = data[i]; // copy elements before position
    }
  }

  delete[] data; // free old array
  data = temp; // point to new array
  size++; // increase size
}

template <typename T>
void List<T>::remove(int position)
{
  if(position < 1 || position > size) {
    throw std::out_of_range("Invalid index: remove"); // invalid position
  }

  if(size == 1) { // if only one element, clear the list
    delete[] data;
    data = new T[0];
    size = 0;
    return;
  }

  T *temp = new T[size - 1];
  for(int i = 0; i < size - 1; i++) {
    if(i >= position - 1) {
      temp[i] = data[i + 1]; // shift elements left after position
    } else {
      temp[i] = data[i]; // copy elements before position
    }
  }
  
  delete[] data; // free old array
  data = temp; // point to new array
  size--; // decrease size
}

template <typename T>
void List<T>::clear()
{
  delete[] data; // free old array
  data = new T[0]; // allocate new empty array
  size = 0; // reset size to zero
}

template <typename T>
T List<T>::getEntry(int position) const
{
  if(position < 1 || position > size){
    throw std::out_of_range("Invalid index: getEntry");
  }
  return data[position - 1]; // return the item at the specified position
}

template <typename T>
void List<T>::setEntry(int position, const T &newValue)
{
 if(position < 1 || position > size){
    throw std::out_of_range("Invalid index: setEntry");
  }
  data[position - 1] = newValue; // set the value at the specified position
}