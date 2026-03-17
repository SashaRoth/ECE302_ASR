/** @file Stack.tpp */
// Finish this link-based Stack to pass unit tests 1~3

#include <stdexcept>
#include "Stack.hpp"
#include "Node.hpp"

template <typename ItemType>
Stack<ItemType>::Stack() : headPtr(nullptr), currentSize(0) {}

template <typename ItemType>
Stack<ItemType>::~Stack()
{
	clear();
}

template <typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	if(currentSize == 0)
		return true;
	else
		return false;
}

template <typename ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}

template <typename ItemType>
bool Stack<ItemType>::push(const ItemType &newItem)
{
	Node<ItemType> *newNodePtr = new Node<ItemType>(newItem, headPtr);
	headPtr = newNodePtr; //make head pointer point to the new node
	newNodePtr = nullptr; //get rid of the original pointer to the new node
	currentSize++; //increment stack size
	return true;
}

template <typename ItemType>
ItemType Stack<ItemType>::peek() const
{	
	if(isEmpty())
		throw std::logic_error("Stack is empty. Cannot peek.");
	else
		return headPtr->getItem();
}

template <typename ItemType>
bool Stack<ItemType>::pop()
{
	if(isEmpty())
		return false;
	else
	{
		Node<ItemType> *nodeToDeletePtr = headPtr; //make a pointer to store the current top node, which will be deleted
		headPtr = headPtr->getNext();			   //increment the headptr				
		nodeToDeletePtr->setNext(nullptr);		   //deallocate the nextptr of the node to be deleted
		delete nodeToDeletePtr;					   //delete the node
		nodeToDeletePtr = nullptr;				   //get rid of the pointer to the deleted node
		currentSize--;							   //decrement stack size		
		return true;
	}
}

template <typename ItemType>
void Stack<ItemType>::clear()
{
	while(!isEmpty())
		pop();
}