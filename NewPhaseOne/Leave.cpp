#include "DEFS.h"
#include "Leave.h"

Leave::Leave(int EventId, TimeHM LT, int PassID, int SS)
{
	this->EventID = EventId;
	EventType = Leav;
	HM = LT;
	this->PassengerID = PassID;
	this->StartS = SS;
}

bool Leave::Execute(Passenger* newps, Station* s)
{;
	return s->RemovePassenger(PassengerID);
}

Leave::~Leave()
{

}
