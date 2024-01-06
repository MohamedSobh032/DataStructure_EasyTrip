#ifndef _LEAVE_H_
#define _LEAVE_H_
#include "Event.h"
class Leave : public Event
{
public:
	Leave(int EventID, TimeHM LT, int PassID, int SS);
	bool Execute(Passenger* newps, Station* s);
	~Leave();
};
#endif

