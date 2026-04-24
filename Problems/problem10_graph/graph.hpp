#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "abstract_graph.hpp"
#include <stack>
#include <queue>

template <typename ItemType>
class Graph : public AbstractGraph<ItemType>
{
private:
    std::map<ItemType, std::set<ItemType>> adjList;
    std::stack<ItemType> DFS_stack;
    std::queue<ItemType> BFS_queue;
    int edgeCount;

public:
    Graph();
    int getNumVertices() const;
    int getNumEdges() const;
    bool add(ItemType start, ItemType end);
    bool remove(ItemType start, ItemType end);
    void depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
    void breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
};

#include "graph.tpp"

#endif