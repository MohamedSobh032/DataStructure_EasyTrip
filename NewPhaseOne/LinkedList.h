#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedList
{
protected:
	Node<T>* Head;
public:

	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	bool peek(T& frntEntry, int ID)
	{
		if (Head == nullptr)
			return false;
		int iterator = 0;
		Node<T>* P = Head;
		while (P->getNext() != nullptr)
		{
			if (iterator == ID)
				break;
			P = P->getNext();
			iterator++;
		}
		if (iterator != ID)
			return false;
		frntEntry = P->getItem();
		return true;
	}

	void InsertEnd(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		Node<T>* P = Head;
		if (Head == nullptr)
			Head = R;
		else
		{
			while (P->getNext() != nullptr)
				P = P->getNext();
			P->setNext(R);
		}
	}

	int CountList()
	{
		Node<T>* P = Head;
		int count = 0;
		while (P)
		{
			P = P->getNext();
			count++;
		}
		return count;
	}
	void DeleteNode(T& value)
	{
		Node<T>* p = Head;
		Node<T>* p1 = p->getNext();
		if (p->getItem() == value)
		{
			Head = p->getNext();
			return;
		}

		while (p1)
		{
			if (p1->getItem() == value)
				p->setNext(p1->getNext());
			p = p->getNext();
			p1 = p1->getNext();
		}
		return;
	}
	//bool DeleteNode(const T& value);
	//bool DeleteNodes(const T& value);

	// Copy Constructor
	LinkedList(const LinkedList& other) : Head(nullptr) {
		Node<T>* current = other.Head;
		while (current != nullptr) {
			InsertBeg(current->getItem());
			current = current->getNext();
		}
	}
};

#endif
