#include "graph.hpp"
#include <queue>

template <typename ItemType>
inline void Graph<ItemType>::visiter(ItemType i)
{
  //std::cout << "Visited " << i << std::endl;
  visitChecker.insert(i);
}

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
  if(adjList.count(start) && adjList[start].count(end)){return false;} //if the start node already has an edge to the end node, return false

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
  bool deleted = false;
  //error checking
  if(start == end){return false;} //if the start node is the end node, return false
  if(!adjList.count(start) || !adjList.count(end)){return false;} //if either node doesn't exist, edge cannot exist
  if(!adjList[start].count(end)){return false;} //if the edge doesn't exist, return false
  
  adjList[start].erase(end); //remove the edge
  adjList[end].erase(start);
  edgeCount--;

  if(adjList[start].empty()){ //if either node now has no edges, remove it
    adjList.erase(start);
    deleted = true;
  }
  if(adjList[end].empty()){
    adjList.erase(end);
    deleted = true;
  }
  if(deleted){return true;}

  depthFirstTraversal(start, [this](ItemType& i){ visiter(i); });
  if(!visitChecker.count(end)){ //if the graph is now disconnected, undo removal
    add(start, end);
    return false;
  }

  return true;
}

template <typename ItemType>
void Graph<ItemType>::depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit)
{
  // TODO, use a stack and similar code structure to breadthFirstTraversal
  std::stack<ItemType> s;
  std::set<ItemType> visited;

  s.push(start);
  visited.insert(start);
  visit(start);

  while(!s.empty()){
    ItemType current = s.top();
    s.pop();

    for(ItemType next : adjList[current]){
      if(!visited.count(next)){
        s.push(next);
        visited.insert(next);
        visit(next);
      }
    }
  }
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
    for (ItemType neighbor : adjList[current]) // TODO: get the neighbors of current
    {
      if (!visited.count(neighbor)) // count is a method in std::set that returns 1 if the item is in the set, and 0 otherwise
      {
        visited.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
}