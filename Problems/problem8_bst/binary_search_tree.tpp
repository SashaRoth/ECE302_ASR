#include "binary_search_tree.hpp"
#include <algorithm>
#include <stack>
#include <stdexcept>

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = nullptr;
} // end default constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root = copyTree(rhs.root);
} // end copy constructor

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType> &BinarySearchTree<KeyType, ItemType>::operator=(BinarySearchTree rhs)
{
    std::swap(root, rhs.root);
    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy(); // delegate to destroy function to deallocate
} // end destructor

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == nullptr);
} // end isEmpty

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(const KeyType &key, ItemType &item)
{
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *curr_parent = nullptr;
    bool found = search(key, curr, curr_parent);
    if (found) {
        item = curr->data;
    } else {
        item = ItemType();
    }
    return found;
} // end retrieve

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    if (root == nullptr) { return; }

    std::stack<Node<KeyType, ItemType>*> storage;
    Node<KeyType, ItemType> *curr = nullptr;
    storage.push(root); // start by pushing the root onto stack

    while (!storage.empty()) {
        curr = storage.top(); // the top of the stack is now the active node
        storage.pop();

        if (curr->right != nullptr) { // push right node
            storage.push(curr->right);
        }
        if (curr->left != nullptr) { // push left node
            storage.push(curr->left);
        }

        delete curr; // deallocate the node after pushing children
    }
    root = nullptr; // avoid dangling root node
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(const KeyType &key, const ItemType &item)
{
    if(root == nullptr){ //if tree is empty, just make the new node the root
        root = new Node<KeyType, ItemType>;
        root->key = key;
        root->data = item;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *currParent = nullptr;
    if(search(key, curr, currParent)){ //if search() returns true, key already exists, cannot insert duplicate
       curr = nullptr;
       currParent = nullptr;
        return false;
    }
    Node<KeyType, ItemType> *newNode = new Node<KeyType, ItemType>; //otherwise, create a new node & insert it as a child of the parent node returned from search()
    newNode->key = key;
    newNode->data = item;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if (key < currParent->key) {
        currParent->left = newNode;
    } else {
        currParent->right = newNode;
    }
    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if(root == nullptr){ //cannot remove from empty tree
        return false;
    }
    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *currParent = nullptr;
    if(!search(key, curr, currParent)){ //if search() returns false, key does not exist, cannot remove
        curr = nullptr;
        currParent = nullptr;
        return false;
    }
    //case if node is a leaf
    else if(curr->left == nullptr && curr->right == nullptr){ 
        if(currParent == nullptr){
            root = nullptr;
        }
        else if(currParent->left == curr){ //if curr is the left child
            currParent->left = nullptr;
        }
        else{ //if curr is the right child
            currParent->right = nullptr;
        }
        delete curr;
        curr = nullptr;
        return true;
    }
    //case if node only has a left child
    else if(curr->left != nullptr && curr->right == nullptr){ 
        if(currParent == nullptr){
            root = curr->left;
        }
        else if(currParent->left == curr){ //if curr is the left child
            currParent->left = curr->left;
        }
        else{ //if curr is the right child
            currParent->right = curr->left;
        }
        delete curr;
        curr = nullptr;
        return true;
    }
    //case if node only has a right child
    else if(curr->left == nullptr && curr->right != nullptr){ 
        if(currParent == nullptr){
            root = curr->right;
        }
        else if(currParent->left == curr){ //if curr is the left child
            currParent->left = curr->right;
        }
        else{ //if curr is the right child
            currParent->right = curr->right;
        }
        delete curr;
        curr = nullptr;
        return true;
    }
    //case if node has two children
    else{ 
        Node<KeyType, ItemType> *successor = nullptr;
        Node<KeyType, ItemType> *successor_parent = nullptr;
        inorder_successor(root, curr, successor, successor_parent);

        Node<KeyType, ItemType> *currLeft = curr->left;  // save curr's children before any pointer changes
        Node<KeyType, ItemType> *currRight = curr->right;

        successor_parent->left = successor->right; //make sure successor's right child doesn't get orphaned

        successor->left = currLeft; //make the successor inherit curr's children
        if (successor != currRight){
            successor->right = currRight;
        }
        
        if (currParent == nullptr){ //if curr is the root, just make successor the root
            root = successor;
        }
        else if (currParent->left == curr){ //if curr is a child, check which one, then assign it to curr_parent
            currParent->left = successor;
        }
        else{
            currParent->right = successor;
        }

        delete curr; //delete & deallocate curr
        curr = nullptr;
        return true;
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int arr_size)
{    
    if(arr_size <= 1){
        return;
    }
    destroy();
    int item = 1;
    for(int i = 0; i < arr_size; i++){
        if(retrieve(arr[i], item)){
            destroy();
            throw std::invalid_argument("Duplicate value found in treeSort()");
        }
        insert(arr[i], item);
    }

    Node<KeyType, ItemType> *curr = nullptr;
    Node<KeyType, ItemType> *successor = nullptr;
    Node<KeyType, ItemType> *successorParent = nullptr;
    
    curr = root;
    while(curr->left != nullptr){ //move to the leftmost node
        curr = curr->left;
    }
    int i = 0;
    while(i < arr_size){
        arr[i] = curr->key; //overwrite the array with in-order values
        inorder_successor(root, curr, successor, successorParent); //iterate through the tree in order
        if(successor == nullptr){break;}
        curr = successor;
        i++;
    }

    // TODO: Implement tree sort using the BST.
    // Hint: Insert all array elements into the BST, throwing an exception if a duplicate is found.
    // Then perform an in-order traversal to collect sorted values and overwrite the input array with them.
    // In-order traversal can be conducted starting from the leftmost node and repeatedly finding the inorder successor.
    // Alternatively, you can find the leftmost node, remove it from the tree, and repeatly find the new leftmost node.
}

// ==================== Private Helper Functions ====================
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder_successor(Node<KeyType, ItemType> *root,
                                                            Node<KeyType, ItemType> *curr,
                                                            Node<KeyType, ItemType> *&inorder,
                                                            Node<KeyType, ItemType> *&inorder_parent)
{
    if (!curr)
    {
        inorder = nullptr;
        inorder_parent = nullptr;
        return;
    }

    // Case 1: Node has right subtree
    // The inorder successor is the leftmost node in the right subtree
    // inorder_parent is tracked in this case
    if (curr->right != nullptr)
    {
        inorder_parent = curr;
        inorder = curr->right;                                 // start with right child
        while (inorder != nullptr && inorder->left != nullptr) // go left until you can't
        {
            inorder_parent = inorder;
            inorder = inorder->left;
        }
        return;
    }

    // Case 2: No right subtree
    // Find the lowest ancestor where curr lies in its left subtree
    // Note: inorder_parent is NOT set in this case
    inorder = nullptr;
    inorder_parent = nullptr;
    Node<KeyType, ItemType> *ancestor = root;
    while (ancestor && ancestor != curr)
    {
        if (curr->key < ancestor->key)
        {
            inorder = ancestor; // potential successor, keep going left to find a closer one
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }
    // inorder now points to the inorder successor (or nullptr if curr is already the largest node)
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::search(KeyType key,
                                                 Node<KeyType, ItemType> *&curr,
                                                 Node<KeyType, ItemType> *&curr_parent)
{
    curr = root;
    curr_parent = nullptr;
    while (curr != nullptr)
    {
        if (key == curr->key) // key is found
            return true;
        curr_parent = curr;
        if (key < curr->key)
            curr = curr->left; // search left subtree
        else
            curr = curr->right; // search right subtree
    }
    return false;
}

template <typename KeyType, typename ItemType>
typename BinarySearchTree<KeyType, ItemType>::template Node<KeyType, ItemType> *
BinarySearchTree<KeyType, ItemType>::copyTree(Node<KeyType, ItemType> *source)
{
    if (!source)
        return nullptr;
    Node<KeyType, ItemType> *newNode = new Node<KeyType, ItemType>;
    newNode->key = source->key;
    newNode->data = source->data;
    newNode->left = copyTree(source->left);
    newNode->right = copyTree(source->right);
    return newNode;
}