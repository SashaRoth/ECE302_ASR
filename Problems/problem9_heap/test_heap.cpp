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

TEST_CASE("Heap: test heap sort + edge cases (Sasha's ver)", "[sort]")
{
   int SashasArray1[] = {-52, 6, 17, 9, 44, 69, 100, 5000};
   ArrayMaxHeap<int> heap(SashasArray1, 8);
   heap.heapSort(SashasArray1, 8);
   REQUIRE(SashasArray1[0] == 5000);
   REQUIRE(SashasArray1[1] == 100);
   REQUIRE(SashasArray1[2] == 69);
   REQUIRE(SashasArray1[3] == 44);
   REQUIRE(SashasArray1[4] == 17);
   REQUIRE(SashasArray1[5] == 9);
   REQUIRE(SashasArray1[6] == 6);
   REQUIRE(SashasArray1[7] == -52);

   //edge case: duplicates
   int SashasArray2[] = {-52, 6, 6, 9, 44, 69, 100, 5000};
   ArrayMaxHeap<int> duplicateheap(SashasArray2, 8);
   REQUIRE_THROWS_AS(duplicateheap.heapSort(SashasArray2, 8), std::invalid_argument); //cannot sort duplicate values

   //edge case: beyond capacity
   char SashasArray3[] = {'h', 'i', ':', '3'}; 
   ArrayMaxHeap<char> bigheap(SashasArray3, 4); 
   //give it a fake out-of-bounds size when calling heapSort
   REQUIRE_THROWS_AS(bigheap.heapSort(SashasArray3, 65), std::invalid_argument); //cannot sort array beyond capacity
}