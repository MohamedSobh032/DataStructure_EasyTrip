#ifndef _EVENT_H_
#define _EVENT_H_
#include "TimeHM.h"
#include "Passenger.h"
#include "Station.h"
class Event
{
protected:
	int EventID;
	bool EventType;
	TimeHM HM;
	int PassengerID;
	int StartS;
	int EndS;
	int PsType;
public:
	Event();
	Event(int ID, bool Type, TimeHM h, int PassID, int StartS, int ES, int PsType);

	void setEventID(int ID);
	int getEventID() const;

	void setEventType(bool Type);
	bool getEventType() const;

	void setHM(TimeHM h);
	TimeHM getHM() const;

	void setPassengerID(int PassID);
	int getPassengerID() const;

	void setStartS(int Start);
	int getStartS() const;

	void setEndS(int E);
	int getEndS() const;

	void setPsType(int PsType);
	int getPsType() const;

	virtual bool Execute(Passenger* newps, Station* s) = 0;

	~Event();
};
#endif
