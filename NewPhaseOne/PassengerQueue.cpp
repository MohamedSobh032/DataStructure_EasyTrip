#include "DEFS.h"
#include "PassengerQueue.h"
#include <iostream>
bool PassengerQueue::RemovePassenger(int ID)
{
	if (isEmpty()) return false;
	else
	{
		Node<Passenger*>* NodeToBeDeleted = frontPtr;
		if (frontPtr->getItem()->getPassengerID() == ID && frontPtr->getItem()->getPassengerType() == NP && frontPtr->getItem()->getPromoted() == NotPromoted)
		{
			if (frontPtr == backPtr)
			{
				frontPtr = nullptr; 
				backPtr = nullptr;
			}
			else
			{
				frontPtr = frontPtr->getNext();
			}
			delete NodeToBeDeleted;
			return true;
		}
		NodeToBeDeleted = frontPtr->getNext();
		Node<Passenger*>* TailPtr = frontPtr;
		while (NodeToBeDeleted != nullptr)
		{
			if (NodeToBeDeleted->getItem()->getPassengerID() == ID && frontPtr->getItem()->getPassengerType() == NP && frontPtr->getItem()->getPromoted() == NotPromoted)
			{
				TailPtr->setNext(NodeToBeDeleted->getNext());
				if (NodeToBeDeleted->getNext() == nullptr)
					backPtr = TailPtr;
				delete NodeToBeDeleted;
				return true;
			}
			else
			{
				NodeToBeDeleted = NodeToBeDeleted->getNext();
				TailPtr = TailPtr->getNext();
			}
		}
		return false;
	}
}

void PassengerQueue::PrintPassengerQueue() const
{
	Node<Passenger*>* current = frontPtr;
	while (current) {
		std::cout << current->getItem()->getPassengerID();
		if (current->getNext() != nullptr) {
			std::cout << " ---> ";
		}
		current = current->getNext();
	}
	std::cout << " ---> NULL" << std::endl;
}

void PassengerQueue::IncrementPassengerWT(int TimeStepInSeconds) {
	int dummy = 0;
	Node<Passenger*>* current = frontPtr;
	while (current) {
		current->getItem()->IncrementWT(TimeStepInSeconds,dummy);
		current = current->getNext();
	}
}

bool PassengerQueue::RemoveFirstPassenger(Passenger*& p)
{
	if (isEmpty())
		return false;
	int dummyprio = 0;
	dequeue(p);
	return true;
}


bool PassengerQueue::PeekSpecific(int& ID, int index)
{
	if (frontPtr == nullptr)
		return false;
	int iterator = 0;
	Node<Passenger*>* P = frontPtr;
	while (P->getNext() != nullptr)
	{
		if (iterator == index)
			break;
		P = P->getNext();
		iterator++;
	}
	if (iterator != index)
		return false;
	ID = P->getItem()->getPassengerID();
	return true;
}

int PassengerQueue::CountSize()
{
	Node<Passenger*>* P = frontPtr;
	int count = 0;
	while (P)
	{
		count++;
		P = P->getNext();
	}
	return count;
}