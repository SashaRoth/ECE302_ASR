#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Construction", "[construction]")
{
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("Test add", "[add]"){
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
  
  REQUIRE(g.add(5, 6));
  
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);

  REQUIRE_FALSE(g.add(5, 5)); //start node cannot be the same as the end node
  REQUIRE_FALSE(g.add(5, 6)); //cannot add a pre-existing edge
  REQUIRE_FALSE(g.add(7, 8)); //adding two new nodes would create a disconnected graph

  REQUIRE(g.getNumVertices() == 2); //invalid add() calls should not change the graph
  REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("Test remove", "[remove]"){
  Graph<int> g;
  REQUIRE(g.add(5, 6));
  REQUIRE(g.add(6, 7));
  REQUIRE(g.add(7, 8));
  REQUIRE(g.getNumEdges() == 3);
  REQUIRE(g.getNumVertices() == 4);

  REQUIRE_FALSE(g.remove(9, 10)); //cannot remove edge from nonexistent verts
  REQUIRE_FALSE(g.remove(5, 7)); //cannot remove nonexistent edge
  REQUIRE_FALSE(g.remove(6, 7)); //cannot remove edge that results in disconnected graph
  REQUIRE(g.getNumEdges() == 3); //counts should remain unchanged
  REQUIRE(g.getNumVertices() == 4);
  
  REQUIRE(g.add(5, 7));
  REQUIRE(g.getNumEdges() == 4); //new edge created, counts update
  REQUIRE(g.getNumVertices() == 4);
  REQUIRE(g.remove(5, 7)); //valid remove
  REQUIRE(g.getNumEdges() == 3); //counts revert
  REQUIRE(g.getNumVertices() == 4);

  REQUIRE(g.remove(7, 8));

  REQUIRE(g.getNumEdges() == 2);
  REQUIRE(g.getNumVertices() == 3); //removing this edge leaves '8' with no edges, so it should be removed

  REQUIRE(g.remove(6, 7)); //remove all edges, this should empty the graph
  REQUIRE(g.remove(5, 6));
  REQUIRE(g.getNumEdges() == 0);
  REQUIRE(g.getNumVertices() == 0);
}

//declare printer function for DFS and BFS tracking
void printer(char c){
    std::cout << "Visited " << c << std::endl;
  }

TEST_CASE("Test DFS", "[depthFirstTraversal]"){
  Graph<char> g;
  
  std::function<void(char)> visit;
  visit = printer;

  REQUIRE(g.add('a', 'b')); //reconstruct example graph from lec 24
  REQUIRE(g.add('a', 'f'));
  REQUIRE(g.add('a', 'i'));
  REQUIRE(g.add('b', 'e'));
  REQUIRE(g.add('b', 'c'));
  REQUIRE(g.add('e', 'c'));
  REQUIRE(g.add('e', 'g'));
  REQUIRE(g.add('c', 'd'));
  REQUIRE(g.add('g', 'd'));
  REQUIRE(g.add('f', 'g'));
  REQUIRE(g.add('d', 'h'));

  std::cout << "Starting Depth-First Traversal" << std::endl;
  g.depthFirstTraversal('a', printer);
  std::cout << std::endl;

}

TEST_CASE("Test BFS", "[breadthFirstTraversal]"){
  Graph<char> g;
  
  std::function<void(char)> visit;
  visit = printer;

  REQUIRE(g.add('a', 'b')); //reconstruct example graph from lec 24
  REQUIRE(g.add('a', 'f'));
  REQUIRE(g.add('a', 'i'));
  REQUIRE(g.add('b', 'e'));
  REQUIRE(g.add('b', 'c'));
  REQUIRE(g.add('e', 'c'));
  REQUIRE(g.add('e', 'g'));
  REQUIRE(g.add('c', 'd'));
  REQUIRE(g.add('g', 'd'));
  REQUIRE(g.add('f', 'g'));
  REQUIRE(g.add('d', 'h'));

  std::cout << "Starting Breadth-First Traversal" << std::endl;
  g.breadthFirstTraversal('a', printer);
  std::cout << std::endl;

}
