#ifndef _ARRIVAL_H_
#define _ARRIVAL_H_
#include "Event.h"
class Arrival : public Event
{
public:
	Arrival(int EventID, int psType, TimeHM AT, int PassID, int SS, int ES);

	void setEndS(int EndS);
	int getEndS() const;

	void setPsType(int PsType);
	int getPsType() const;

	bool Execute(Passenger* newps, Station* s);
	~Arrival();
};
#endif

