// A class template for holding a linked list.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "stdafx.h"
#include <iostream>		// For cout and NULL
using namespace std;

template <class T>
class LinkedList
{
private:
	// Declare a structure for the list
	struct ListNode
	{
		T value;
		struct ListNode *next;
	}; 

	ListNode *head;				// List head pointer
	ListNode *placeHolder;		// New member for incremetally traversing the list

public:
	LinkedList()	// Constructor
		{ head = NULL; placeHolder = NULL; }
	~LinkedList(); // Destructor
	void appendNode(T);
	void insertNode(T);
	void deleteNode(T);
	void displayList();
	// New functions added for this exercise.
	bool getFirst(T &);
	bool getNext(T &);
};


//**************************************************
// appendNode appends a node containing the value  *
// pased into newValue, to the end of the list.    *
//**************************************************

template <class T>
void LinkedList<T>::appendNode(T newValue)
{
	ListNode *newNode, *nodePtr;

	// Allocate a new node & store newValue
	newNode = new ListNode;
	newNode->value = newValue;
	newNode->next = NULL;

	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
		head = newNode;
	else	// Otherwise, insert newNode at end
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Find the last node in the list
		while (nodePtr->next)
			nodePtr = nodePtr->next;

		// Insert newNode as the last node
		nodePtr->next = newNode;
	}
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

template <class T>
void LinkedList<T>::displayList()
{
	ListNode *nodePtr;

	nodePtr = head;
	while (nodePtr)
	{
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
	ListNode *newNode, *nodePtr, *previousNode = NULL;

	// Allocate a new node & store newValue
	newNode = new ListNode;
	newNode->value = newValue;
	
	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert newNode
	{
		// Initialize nodePtr to head of list and previousNode to NULL.
		nodePtr = head;
		previousNode = NULL;

		// Skip all nodes whose value member is less
		// than newValue.
		while (nodePtr != NULL && nodePtr->value < newValue)
		{	
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == NULL)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else	// Otherwise, insert it after the prev. node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
	ListNode *nodePtr, *previousNode;

	// If the list is empty, do nothing.
	if (!head)
		return;
	
	// Determine if the first node is the one.
	if (head->value == searchValue)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is 
		// not equal to searchValue.
		while (nodePtr != NULL && nodePtr->value != searchValue)
		{	
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If nodePtr is not at the end of the list, 
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
	ListNode *nodePtr, *nextNode;

	nodePtr = head;
	while (nodePtr != NULL)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}


//**************************************************
// If the linked list contains any data, this      *
// function stores the value of the first node in  *
// the reference parameter var, and returns true.  *
// If the list contains no data, the function      *
// returns false.                                  *
//**************************************************

template <class T>
bool LinkedList<T>::getFirst(T &var)
{
	bool status;

	placeHolder = head;
	if (placeHolder)
	{
		var = placeHolder->value;
		status = true;
	}
	else
	{
		status = false;
	}
	return status;
}

//***************************************************
// If the placeHolder pointer is pointing to a      *
// valid node, it is moved to the next node. If     *
// that node is valid, the value stored in the node *
// assigned to the reference parameter var, and the *
// function returns true. If the node that          *
// placeHolder currently points to is not valid, or *
// the next node is not valid, this function        *
// returns false.                                   *
//***************************************************

template <class T>
bool LinkedList<T>::getNext(T &var)
{
	bool status;

	if (placeHolder)
	{
		placeHolder = placeHolder->next;
		if (placeHolder)
		{
			var = placeHolder->value;
			status = true;
		}
		else
		{
			status = false;
		}
	}
	else
	{
		status = false;
	}
	return status;
}

#endif