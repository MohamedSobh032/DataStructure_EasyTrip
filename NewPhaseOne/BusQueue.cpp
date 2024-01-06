#include "BusQueue.h"
#include "DEFS.h"
#include <iostream>

int BusQueue::IncrementTimeNotInStation(int TimeBetweenStationInMinutes, int StepSizeInSeconds)
{
	int counter = 0;
	Node<Bus*>* p = frontPtr;
	while (p)
	{
		if (p->getItem()->IncrementTimeNotInStation(TimeBetweenStationInMinutes, StepSizeInSeconds))
			counter++;
		p = p->getNext();
	}
	return counter;
}

void BusQueue::IncrementTimeInStation(int StepSizeInSeconds, int SID)
{
	Node<Bus*>* p = frontPtr;
	while (p)
	{
		p->getItem()->IncrementTotalTimeInStation(StepSizeInSeconds, SID);
		p = p->getNext();
	}
}

void BusQueue::DecrementMaintenanceTimeQueue(int TimeStepInSeconds)
{
	Node<Bus*>* p = frontPtr;
	while (p)
	{
		p->getItem()->DecrementMaintenanceTime(TimeStepInSeconds);
		p = p->getNext();
	}
}


int BusQueue::CountMBBus()
{
	int count = 0;
	Node<Bus*>* p = frontPtr;
	while (p)
	{
		if (p->getItem()->getBusType() == MB)
			count++;
		p = p->getNext();
	}
	return count;
}
int BusQueue::CountWBBus()
{
	int count = 0;
	Node<Bus*>* p = frontPtr;
	while (p)
	{
		if (p->getItem()->getBusType() == WB)
			count++;
		p = p->getNext();
	}
	return count;
}


bool BusQueue::PeekBus(int& ID, bool& Type, int& CurrentCap, int maxc, int index)
{
	Node<Bus*>* p = frontPtr;
	if (p != nullptr)
	{
		int i = 0;
		while (p)
		{
			if (i == index)
				break;
			p = p->getNext();
			i++;
		}
		if (i != index)
			return false;
		else
		{
			ID = p->getItem()->getBusID();
			Type = p->getItem()->getBusType();
			CurrentCap = p->getItem()->getAvailablePassenger(maxc);
			return true;
		}
	}
	return false;
}
bool BusQueue::PeekPassengerOnBus(int busindex, int& PID, int index)
{
	Node<Bus*>* p = frontPtr;
	int i = 0;
	while (p)
	{
		if (i == busindex)
			break;
		p = p->getNext();
		i++;
	}
	if (i != busindex)
		return false;
	
	p->getItem()->getPassenger(index, PID);


}


int BusQueue::CountPassengerOnBus(int busid)
{
	Node<Bus*>* p = frontPtr;
	int i = 0;
	while (p)
	{
		if (i == busid)
			break;
		p = p->getNext();
		i++;
	}
	if (i != busid)
		return false;

	return p->getItem()->getCurrentPassenger();
}