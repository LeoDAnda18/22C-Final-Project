#ifndef NODE_H
#define NODE_H

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
#endif // !NODE_H

//
//#ifndef NODE_H
//#define NODE_H
//
//#include <iostream>
//#include <string>
//
//template <class T>
//class Node
//{
//public:
//	T data;
//	Node<T> *leftBranch;
//	Node<T> *rightBranch;
//
//	// defualt constructor
//	Node()
//	{
//		leftBranch = nullptr;
//		rightBranch = nullptr;
//	}
//
//	// constructor
//	Node(T value)
//	{
//		data = value;
//		leftBranch = nullptr;
//		rightBranch = nullptr;
//	}
//};
//
//#endif // !NODE_H