#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ArrayMaxHeap.hpp"

/* Provided test cases */
TEST_CASE("Heap: test construct from array", "[construct]")
{
   int array[] = {80, 70, 60, 50, 40, 30, 20, 10};
   ArrayMaxHeap<int> heap(array, 8);
   REQUIRE(heap.getNumberOfNodes() == 8);
   REQUIRE(heap.getHeight() == 4);
   REQUIRE(heap.isEmpty() == false);
   heap.clear();
   REQUIRE(heap.getNumberOfNodes() == 0);
   REQUIRE(heap.getHeight() == 0);
   REQUIRE(heap.isEmpty() == true);
}

/*
TEST_CASE("Heap: test heap sort", "[sort]")
{
   int array[] = {15, 5, 20, 10, 30};
   ArrayMaxHeap<int> heap(array, 5);
   heap.heapSort(array, 5);
   REQUIRE(array[0] == 30);
   REQUIRE(array[1] == 20);
   REQUIRE(array[2] == 15);
   REQUIRE(array[3] == 10);
   REQUIRE(array[4] == 5);
}
*/

/* Additional test cases */
TEST_CASE("Heap: test peekTop, remove, add", "[peekTop]"){
   int array[] = {80, 20, 60, 50, 15, 30, 20, 90};
   ArrayMaxHeap<int> heap(array, 8); //upon constructor call, heapRebuild() is called
   REQUIRE(!heap.isEmpty());

   REQUIRE(heap.peekTop() == 90); //heapRebuild should have moved 90 to the root

   REQUIRE(heap.remove()); //remove should return true, heap is not empty
   REQUIRE(heap.peekTop() == 80); //80 should have sifted to the top

   REQUIRE(heap.add(70)); //heap is not at capacity, should allow add
   REQUIRE(heap.peekTop() == 80); //70 < 80, should not have sifted up
   REQUIRE(heap.add(100));
   REQUIRE(heap.peekTop() == 100); //100 > 80, should have sifted to the top
}

TEST_CASE("Heap: test peekTop, remove, add edge cases"){
   int emptyArray[] = {};
   ArrayMaxHeap<int> emptyHeap(emptyArray, 0); //begin with empty array
   REQUIRE(emptyHeap.isEmpty());

   REQUIRE_FALSE(emptyHeap.remove()); //cannot remove from empty heap
   REQUIRE_THROWS_AS(emptyHeap.peekTop(), std::out_of_range); //peeking an empty heap should throw an error

   int fullArray[] = {80, 20, 60, 50, 15, 30, 20, 90, 80, 20, 60, 50, 15, 30, 20, 90, 80, 20, 60, 50, 15, 30, 20, 90, 80, 20, 60, 50, 15, 30, 20};
   ArrayMaxHeap<int> fullHeap(fullArray, 63); //upon constructor call, heapRebuild() is called

   REQUIRE_FALSE(fullHeap.add(1)); //cannot add to full heap
}