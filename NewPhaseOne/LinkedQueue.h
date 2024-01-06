#ifndef _LINKED_QUEUE_H_
#define _LINKED_QUEUE_H_

#include "Node.h"

template <typename T>
class LinkedQueue
{
protected:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;
public:
	LinkedQueue();

	int getCount() const { return count; }

	bool isEmpty() const;

	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)	const;

	~LinkedQueue();
	//Copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
	//Assignment operator
	LinkedQueue<T>& operator=(const LinkedQueue<T>& other)
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
LinkedQueue<T>::LinkedQueue()
{
	frontPtr = nullptr;
	backPtr = nullptr;
	count = 0;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (isEmpty())
		frontPtr = newNodePtr;
	else
		backPtr->setNext(newNodePtr);
	backPtr = newNodePtr;
	count++;
	return true;
}

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;
	count--;
	Node<T>* NodeToBeDeleted = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if (NodeToBeDeleted == backPtr)
		backPtr = nullptr;
	delete NodeToBeDeleted;
	return true;
}

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;
	frntEntry = frontPtr->getItem();
	return true;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;
	while (dequeue(temp)) { ; }
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr)			//check if empty linkedqueue or not
	{
		frontPtr = backPtr = nullptr;
		this->count = LQ.count;
		return;
	}
	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
	this->count = LQ.count;
}


#endif
