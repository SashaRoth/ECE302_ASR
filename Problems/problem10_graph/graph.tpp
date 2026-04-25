#include "graph.hpp"
#include <queue>

template <typename ItemType>
Graph<ItemType>::Graph()
{
  edgeCount = 0;
}

template <typename ItemType>
int Graph<ItemType>::getNumVertices() const
{
  return adjList.size();
}

template <typename ItemType>
int Graph<ItemType>::getNumEdges() const
{
  return edgeCount;
}

template <typename ItemType>
bool Graph<ItemType>::add(ItemType start, ItemType end)
{
  //error checking
  if(start == end){return false;} //if the start node is the end node, return false
  if(!adjList.count(start) && !adjList.count(end) && !adjList.empty()){return false;} //if both verts are new and the graph is not empty, insertion would create a disconnected graph
  if(adjList[start].count(end)){return false;} //if the start node already has an edge to the end node, return false

  //insertion procedure
  if(!adjList.count(start)){ //add start if not already there
    adjList.emplace(start, std::set<ItemType>{});
  }
  if(!adjList.count(end)){ //add end if not already there
    adjList.emplace(end, std::set<ItemType>{});
  }
  adjList[start].insert(end); //add edge from start-->end
  adjList[end].insert(start); //add edge from end-->start
  edgeCount++;
  
  return true;
}

template <typename ItemType>
bool Graph<ItemType>::remove(ItemType start, ItemType end)
{
  // TODO
  return false; // Placeholder
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // TODO, use a stack and similar code structure to breadthFirstTraversal
}

template <typename ItemType>
void Graph<ItemType>::breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  std::queue<ItemType> q;
  std::set<ItemType> visited; // set is a container that stores unique items in sorted order, and provides fast lookup
  q.push(start);
  visited.insert(start);
  while (!q.empty())
  {
    ItemType current = q.front();
    q.pop();
    visit(current);
    for (ItemType neighbor : std::vector<ItemType>{}) // TODO: get the neighbors of current
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
}