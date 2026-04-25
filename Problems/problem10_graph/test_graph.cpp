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

TEST_CASE("Test Add", "[add]"){
  Graph<int> g;
  REQUIRE(g.getNumVertices() == 0);
  REQUIRE(g.getNumEdges() == 0);
  
  REQUIRE(g.add(5, 6));
  
  REQUIRE(g.getNumVertices() == 2);
  REQUIRE(g.getNumEdges() == 1);
}