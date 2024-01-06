#ifndef _PASSENGER_PRIO_QUEUE_H_
#define _PASSENGER_PRIO_QUEUE_H_
#include "LinkedPrioQueue.h"
#include "Passenger.h"
class PassengerPrioQueue : public LinkedPrioQueue<Passenger*>
{
public:
	bool RemovePassenger(int ID);
	void PrintPassengerPrioQueue() const;
	bool IncrementPassengerWT(int TimeStepInSeconds,int maxWT);
	bool RemoveFirstTypePassenger(Passenger*& p, bool NormalOrNot);
	bool PeekSpecific(int& ID, int& prio, int index);
	int CountSize(bool CountNormal);
};

#endif /* _PASSENGER_PRIO_QUEUE_H_ */

