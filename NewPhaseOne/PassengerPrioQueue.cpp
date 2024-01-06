#include "DEFS.h"
#include "PassengerPrioQueue.h"
#include <iostream>



bool PassengerPrioQueue::RemovePassenger(int ID)
{
	if (isEmpty()) return false;
	else
	{
		PrioNode<Passenger*>* NodeToBeDeleted = frontPtr;
		if (frontPtr->getItem()->getPassengerID() == ID && frontPtr->getItem()->getPassengerType() == NP)
		{
			if (frontPtr == backPtr)
			{
				frontPtr = backPtr = nullptr;
			}
			else
			{
				frontPtr = frontPtr->getNext();
			}
			delete NodeToBeDeleted;
			return true;
		}
		NodeToBeDeleted = NodeToBeDeleted->getNext();
		PrioNode<Passenger*>* TailPtr = frontPtr;
		while (NodeToBeDeleted != nullptr)
		{
			if (NodeToBeDeleted->getItem()->getPassengerID() == ID && frontPtr->getItem()->getPassengerType() == NP)
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

void PassengerPrioQueue::PrintPassengerPrioQueue() const
{
	PrioNode<Passenger*>* current = frontPtr;
	while (current) {
		std::cout << current->getItem()->getPassengerID();
		if (current->getNext() != nullptr) {
			std::cout << " ---> ";
		}
		current = current->getNext();
	}
	std::cout << " ---> " << "NULL" << std::endl;
}

bool PassengerPrioQueue::IncrementPassengerWT(int TimeStepInSeconds, int maxWT) {
	if (isEmpty())
		return false;
	if (frontPtr == backPtr) {
		frontPtr->getItem()->IncrementWT(TimeStepInSeconds,maxWT);
		return true;
	}
	PrioNode<Passenger*>* tail = frontPtr;
	tail->getItem()->IncrementWT(TimeStepInSeconds,maxWT);
	PrioNode<Passenger*>* current = tail->getNext();
	while (current) {
		if (current->getItem()->IncrementWT(TimeStepInSeconds,maxWT))
		{
			current->getItem()->setPromoted();
			tail->setNext(current->getNext());
			current->setNext(frontPtr);
			frontPtr = current;
			current = tail->getNext();
		}
		else
		{
			current = current->getNext();
			tail = tail->getNext();
		}
	}
	return true;
}

bool PassengerPrioQueue::RemoveFirstTypePassenger(Passenger*& p, bool NormalOrNot)
{
	int dummyprio = 0;
	if (isEmpty())
		return false;
	else if (NormalOrNot == true && (frontPtr->getItem()->getPassengerType() == NP || frontPtr->getItem()->getPassengerType() == PNP))
	{
		dequeue(dummyprio,p);
		return true;
	}
	else if (NormalOrNot == false && frontPtr->getItem()->getPassengerType() != NP && frontPtr->getItem()->getPassengerType() != PNP)
	{
		dequeue(dummyprio,p);
		return true;
	}
	else if (frontPtr == backPtr)
	{
		return false;
	}
	else
	{
		PrioNode<Passenger*>* current = frontPtr->getNext();
		PrioNode<Passenger*>* tail = frontPtr;
		while (current) {
			int Type = current->getItem()->getPassengerType();
			if (NormalOrNot == true && (Type == NP || Type == PNP))
			{
				tail->setNext(current->getNext());
				p = current->getItem();
				return true;
			}
			else if (NormalOrNot == false && Type != NP && Type != PNP)
			{
				tail->setNext(current->getNext());
				p = current->getItem();
				return true;
			}
			else
			{
				current = current->getNext();
				tail = tail->getNext();
			}
		}
		return false;
	}
}

bool PassengerPrioQueue::PeekSpecific(int& ID, int& prio, int index)
{
	if (frontPtr == nullptr)
		return false;
	int iterator = 0;
	PrioNode<Passenger*>* P = frontPtr;
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
	prio = P->getPrio();
	return true;
}

int PassengerPrioQueue::CountSize(bool CountNormal)
{
	PrioNode<Passenger*>* P = frontPtr;
	int count = 0;
	if (CountNormal == true)
	{
		while (P)
		{
			if (P->getPrio() == PNP)
				count++;
			if (P->getPrio() == NP)
				count++;
			P = P->getNext();
		}
	}
	else
	{
		while (P)
		{
			if (P->getPrio() != PNP && P->getPrio() != NP) 
				count++;
			P = P->getNext();
		}
	}
	return count;
}