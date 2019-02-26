/*
This file contains:
Linked List
Stack
Queue
BST
*/

#ifndef LEOLINKEDLIST_H
#define LEOLINKEDLIST_H

//#include "LeoNode.h"
#include <fstream>
#include <iostream>
#include <string>

template <class T>
class Node
{
private:
	T data;
	Node<T>* ptrFront;
	Node<T>* ptrRear;
public:
	//Constructors
	Node()
	{
		ptrFront = nullptr;
		ptrRear = nullptr;
	}
	Node(T &D)
	{
		data = D;
		ptrFront = nullptr;
		ptrRear = nullptr;
	}
	Node(T &D, Node<T>* ptrN)
	{
		data = D;
		ptrFront = ptrN;
		ptrRear = nullptr;
	}
	Node(T &D, Node<T>* ptrN, Node<T>* ptrR)
	{
		data = D;
		ptrFront = ptrN;
		ptrRear = ptrR;
	}

	//Setters
	void setData(T &d)
	{
		data = d;
	}
	void setPtrFront(Node<T>* pF)
	{
		ptrFront = pF;
	}
	void setPtrRear(Node<T>* pR)
	{
		ptrRear = pR;
	}


	//Getters
	T getData() const
	{
		return data;
	}
	Node<T>* getPtrFront() const
	{
		return ptrFront;
	}
	Node<T>* getPtrRear() const
	{
		return ptrRear;
	}

};
//#endif // !NODE_H






template <class T>
class LinkedList
{
private:
	Node<T>* headPtr;
	int itemCount;
	Node<T>* rearPtr;
public:
	//Constructor
	LinkedList()
	{
		headPtr = nullptr;
		rearPtr = nullptr;
		itemCount = 0;
	}

	//Destructor
	virtual ~LinkedList()
	{
		cout << "Calling the clear function" << endl;
		clear();
		cout << "Destroying the link-list" << endl;
	}

	/*This function returns the size of a link-list
	Pre:
	Post:
	Return: size of the link-list
	*/
	int getCurrentSize() const
	{
		return itemCount;
	}

	/*This function checks to see if a link list is empty (has 0 nodes)
	Pre:
	Post:
	Return: true or false
	*/
	bool isEmpty() const
	{
		return (headPtr == nullptr);
	}

	/*This function adds a defined node into a link-list.
	Pre: index - an integer value
	newNode - a pointer to a node
	Post: If the operation is successful, newNode is added to the link list at position index.
	Return: True or false
	*/
	bool addAnywhere(int index, Node<T>* newNode)
	{
		bool isSuccess = false;
		if (index >= 0 && index <= itemCount)
		{
			Node<T> *curPtr = headPtr;
			Node<T> *prevPtr = nullptr;
			int i = 0;
			while (i < index)
			{
				prevPtr = curPtr;
				curPtr = curPtr->getPtrFront();
				i++;
			}
			newNode->setPtrFront(curPtr);
			if (prevPtr == nullptr)
				headPtr = newNode;
			else
				prevPtr->setPtrFront(newNode);
			itemCount++;
			isSuccess = true;
			return isSuccess;
		}
		else
			return isSuccess;
	}

	/*This function removes a node from a link-list
	Pre: index - an integer value
	Post: if the operation is successful, then the node at position index is removed from the link list.
	Return: true or false
	*/
	bool removeAnywhere(int index)
	{
		bool isSuccess = false;
		if (index >= 0 && index < itemCount)
		{
			Node<T> *curPtr = headPtr;
			Node<T> *prevPtr = nullptr;
			int i = 0;
			while (i < index)
			{
				prevPtr = curPtr;
				curPtr = curPtr->getPtrFront();
				i++;
			}
			if (prevPtr == nullptr)
				headPtr = curPtr->getPtrFront();
			else
				prevPtr->setPtrFront(curPtr->getPtrFront());
			curPtr->setPtrFront(nullptr);
			delete curPtr;
			curPtr = nullptr;
			itemCount--;
			isSuccess = true;
			return isSuccess;
		}
		else
			return isSuccess;
	}

	/*This function searches for a specific piece of data in a link-list
	Pre: searchEntry - a variable holding a value depending on the data type
	Post:
	Return: index (an integer), -1, or -2
	*/
	int searchAnywhere(T searchEntry)
	{
		if (itemCount > 0)
		{
			int index = 0;
			Node<T> *curPtr = headPtr;
			while (curPtr->getData() != searchEntry && curPtr->getPtrFront() != nullptr)
			{
				curPtr = curPtr->getPtrFront();
				index++;
			}
			if (curPtr->getData() == searchEntry)
				return index; // Data found
			else
				return -1; // Data not found
		}
		else
			return -2; // Link List doesn't have any nodes.
	}

	/*This function returns a pointer to a node in the link-list.
	Pre: index - an integer value
	Post:
	Return: curPtr - pointer to a node
	*/
	Node<T>* obtainDataAnywhere(int index)
	{
		Node<T> *curPtr = headPtr;
		if (itemCount > 0 && index < itemCount)
		{
			int i = 0;
			while (i < index)
			{
				curPtr = curPtr->getPtrFront();
				i++;
			}
			return curPtr;
		}
		else
			return nullptr;
	}

	/*This function removes all nodes in a link-list
	Pre:
	Post: If the operation is successful, all nodes in a link list are destroyed and the itemCount is set to 0.
	Return:
	*/
	void clear()
	{
		while (headPtr != nullptr)
		{
			Node<T>* deletePtr = headPtr;
			headPtr = headPtr->getPtrFront();
			deletePtr->setPtrFront(nullptr);
			delete deletePtr;
			deletePtr = nullptr;
		}
		itemCount = 0;
	}

	//Setters
	void setCount(int c)
	{
		itemCount = 0;
	}
	void setHeadPtr(Node<T>* ptr)
	{
		headPtr = ptr;
		itemCount++;
	}
	void setRearPtr(Node<T>* rPtr)
	{
		rearPtr = rPtr;
	}

	//Getters
	int getCount()
	{
		return itemCount;
	}
	Node<T>* getHeadPtr()
	{
		return headPtr;
	}
	Node<T>* getRearPtr()
	{
		return rearPtr;
	}
};

#endif // !_LINKED_LIST