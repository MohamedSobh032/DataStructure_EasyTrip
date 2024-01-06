#ifndef _LINKED_PRIO_QUEUE_H_
#define _LINKED_PRIO_QUEUE_H_
#include "PrioNode.h"
template <typename T>
class LinkedPrioQueue
{
protected:
	PrioNode<T>* frontPtr;
	PrioNode<T>* backPtr;
public:
	LinkedPrioQueue();

	bool isEmpty() const;

	bool enqueue(int prio, const T& newEntry);
	bool dequeue(int& prio, T& frntEntry);
	bool peek(int& prio, T& frntEntry)	const;

	~LinkedPrioQueue();
	//Copy constructor
	LinkedPrioQueue(const LinkedPrioQueue<T>& LQ);
	//Assignment operator
	LinkedPrioQueue<T>& operator=(const LinkedPrioQueue<T>& other)
	{
		if (this == &other) {
			return *this;  // If assigning to itself, return itself
		}

		// Clear the current queue
		// ... (Implement your own clear function)

		// Copy the elements from the other queue
		// ... (Implement your own copy function)

		return *this;
	}
};

template <typename T>
LinkedPrioQueue<T>::LinkedPrioQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

template <typename T>
bool LinkedPrioQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
bool LinkedPrioQueue<T>::enqueue(int prio, const T& newEntry)
{
	PrioNode<T>* newNode = new PrioNode<T>(prio, newEntry); 
	if (isEmpty()) {
		frontPtr = newNode;
		backPtr = newNode;
	}
	else
	{
		if (newNode->getPrio() <= frontPtr->getPrio())
		{
			newNode->setNext(frontPtr);
			frontPtr = newNode;
		}
		else
		{
			PrioNode<T>* prev = frontPtr;
			PrioNode<T>* temp = frontPtr;
			while (temp && newNode->getPrio() >= temp->getPrio())
			{
				prev = temp;
				temp = temp->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(temp);
		}
	}
	return true;
}

template <typename T>
bool LinkedPrioQueue<T>::dequeue(int& prio, T& frntEntry)
{
	if (isEmpty())
		return false;
	prio = frontPtr->getPrio();
	PrioNode<T>* NodeToBeDeleted = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if (NodeToBeDeleted == backPtr)
		backPtr = nullptr;
	delete NodeToBeDeleted;
	return true;
}

template <typename T>
bool LinkedPrioQueue<T>::peek(int& prio, T& frntEntry) const
{
	if (isEmpty())
		return false;
	prio = frontPtr->getPrio();
	frntEntry = frontPtr->getItem();
	return true;
}

template <typename T>
LinkedPrioQueue<T>::~LinkedPrioQueue()
{
	int prio;
	T temp;
	//Free (Dequeue) all nodes in the queue
	while (dequeue(prio, temp));
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/
template <typename T>
LinkedPrioQueue<T>::LinkedPrioQueue(const LinkedPrioQueue<T>& LQ)
{
	PrioNode<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	PrioNode<T>* ptr = new PrioNode<T>(NodePtr->getPrio(), NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		PrioNode<T>* ptr = new PrioNode<T>(NodePtr->getPrio(), NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif