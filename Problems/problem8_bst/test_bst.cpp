#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.hpp"

using key = int;
using TreeType = BinarySearchTree<key, int>;

/* Provided test cases */
TEST_CASE("BST: Test Insert", "[insert]")
{
    TreeType bst1;
    REQUIRE(bst1.isEmpty());

    bst1.insert(10, 10);
    REQUIRE_FALSE(bst1.isEmpty());
}

TEST_CASE("BST: Test Duplicate Insert", "[duplicate insert]")
{
    TreeType bst1;
    REQUIRE(bst1.insert(12, 12));
    REQUIRE_FALSE(bst1.insert(12, 12));
}

TEST_CASE("BST: Test Remove With No Children", "[remove]")
{
    TreeType bst1;
    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);

    int item;

    REQUIRE(bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(15, item));

    bst1.remove(5);
    REQUIRE_FALSE(bst1.retrieve(5, item));

    bst1.remove(15);
    REQUIRE_FALSE(bst1.retrieve(15, item));

    bst1.remove(10);
    REQUIRE_FALSE(bst1.retrieve(10, item));

    REQUIRE(bst1.isEmpty());
}


TEST_CASE("BST: Test Destroy after Copy Assign", "[copy assign]")
{
    TreeType bst1;
    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;
    bst2 = bst1;

    bst1.destroy();
    REQUIRE(bst1.isEmpty());
    REQUIRE_FALSE(bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE_FALSE(bst2.retrieve(51, item));
}
    
/* Write your own test cases here */

//destroy
TEST_CASE("BST: Test destroy() method and edge cases", "[destroy]"){
    int item;
    TreeType SashasBST;
    SashasBST.destroy(); //edge case: destroy should run fine on an empty tree

    SashasBST.insert(1, 2);
    SashasBST.insert(3, 4);
    SashasBST.insert(5, 6);

    REQUIRE(!SashasBST.isEmpty());

    SashasBST.destroy();

    REQUIRE(SashasBST.isEmpty()); //tree should be empty now

}

//insert
TEST_CASE("BST: Test insert() method and edge cases", "[insert]"){
    int item = 302;
    TreeType SashasBST;

    REQUIRE(SashasBST.insert(1, item)); //should be able to insert item into empty tree
    REQUIRE(SashasBST.insert(2, item)); //should be able to insert duplicate value with different key

    REQUIRE_FALSE(SashasBST.insert(1, item)); //should NOT be able to insert item with duplicate key
}

//remove
TEST_CASE("BST: Test remove() method and edge cases", "[remove]"){
    int item = 302;
    TreeType SashasBST;

    REQUIRE_FALSE(SashasBST.remove(1)); //cannot remove from empty tree

    SashasBST.insert(7, item);
    SashasBST.insert(3, item);
    SashasBST.insert(9, item);
    SashasBST.insert(2, item);
    SashasBST.insert(4, item);
    SashasBST.insert(8, item);
    SashasBST.insert(10, item);
    /*
            7
          /   \
        3       9
       / \     / \
      2   4   8   10
    */
    REQUIRE_FALSE(SashasBST.remove(1)); //cannot remove value that does not exist
    REQUIRE(SashasBST.remove(7)); //should be able to remove root
    REQUIRE(SashasBST.remove(2)); //should be able to remove leaf
}
//treeSort
TEST_CASE("BST: Test treeSort() method", "[treeSort]"){
    TreeType SashasBST;
    int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int arr_size = 9;
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    SashasBST.treeSort(arr, arr_size);

    for(int i = 0; i < arr_size; i++){
        REQUIRE(arr[i] == expected[i]);
    }
}

TEST_CASE("BST: Test treeSort() with empty array", "[treeSort]"){
    TreeType SashasBST;
    int arr[] = {};
    int arr_size = 0;

    SashasBST.treeSort(arr, arr_size); // Should not crash
}

TEST_CASE("BST: Test treeSort() with single element", "[treeSort]"){
    TreeType SashasBST;
    int arr[] = {302};
    int arr_size = 1;

    SashasBST.treeSort(arr, arr_size);

    REQUIRE(arr[0] == 302);
}

TEST_CASE("BST: Test treeSort() with duplicates throws exception", "[treeSort]"){
    TreeType SashasBST;
    int arr[] = {1, 2, 2, 3};
    int arr_size = 4;

    REQUIRE_THROWS_AS(SashasBST.treeSort(arr, arr_size), std::invalid_argument);
}

