#include "frontier_queue.hpp"
#include <stdexcept>

// Min-heap index helpers:
//   parent of i      : (i - 1) / 2
//   left  child of i : 2 * i + 1
//   right child of i : 2 * i + 2

template <typename T>
State<T> frontier_queue<T>::pop()
{
  if(empty()){
    throw std::out_of_range("Cannot pop from empty vector");
  }
  int end = queue.size() - 1;
  std::swap(queue[0], queue[end]);

  State<T> toReturn = queue[end];
  queue.pop_back();

  int current_idx = 0;
  while(2 * current_idx + 1 < queue.size()){
    int left_child = (2*current_idx) + 1;
    int right_child = (2*current_idx) + 2;
    int smallest = current_idx;
      if (left_child < queue.size()
        && queue[left_child].getFCost() < queue[smallest].getFCost()) {
        smallest = left_child;
      }
      if (right_child < queue.size()
        && queue[right_child].getFCost() < queue[smallest].getFCost()) {
        smallest = right_child;
      }
      if (smallest != current_idx) {
        std::swap(queue[current_idx], queue[smallest]);
        current_idx = smallest;
      }
      else {
        break;
      }
  }
  return toReturn;
}

template <typename T>
void frontier_queue<T>::push(const T &state, int cost, int heur)
{
  State<T> newEntry(state, cost, heur);
  queue.push_back(newEntry);
  if(queue.size() == 1){return;} //if newEntry is the only entry, no need to do comparisons

  int current_idx = queue.size() - 1;

  while(current_idx > 0){
    int parent_idx = (current_idx - 1)/2;
    if(newEntry.getFCost() < queue[parent_idx].getFCost()){
      std::swap(queue[parent_idx], queue[current_idx]);
      current_idx = parent_idx;
    }else{break;}
  }
}

template <typename T>
bool frontier_queue<T>::empty()
{
  return queue.empty();
}

template <typename T>
bool frontier_queue<T>::contains(const T &state)
{
  for(auto it = queue.begin(); it < queue.end(); it++){
    if(it->getValue() == state){return true;}
  }
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &state, int cost)
{
  for(auto it = queue.begin(); it < queue.end(); it++){
    if(it->getValue() == state && cost < it->getPathCost()){
      it->updatePathCost(cost);
    }
  }
}

template <typename T>
int frontier_queue<T>::getCurrentPathCost(const T &state)
{
  for(State<T> item : queue){
    if(item.getValue() == state){
      return item.getPathCost();
    }
  }
  return -1;
}