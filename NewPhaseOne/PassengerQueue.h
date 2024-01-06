#ifndef _PASSENGER_QUEUE_H_
#define _PASSENGER_QUEUE_H_
#include "Passenger.h"	
#include "LinkedQueue.h"
class PassengerQueue  : public LinkedQueue<Passenger*>
{
public:
	bool RemovePassenger(int ID);
	void PrintPassengerQueue() const;
	void IncrementPassengerWT(int TimeStepInSeconds);
	bool RemoveFirstPassenger(Passenger*& p);
	bool PeekSpecific(int& ID, int index);
	int CountSize();
};

#endif
