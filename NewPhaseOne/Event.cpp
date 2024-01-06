#include "Event.h"

Event::Event()
{
	EventID = 0;
	EventType = 0;
	HM = 0;
	PassengerID = 0;
	StartS = 0;
}
Event::Event(int ID, bool Type, TimeHM h, int PassID, int StartS, int ES, int PsType)
{
	this->EventID = ID;
	this->EventType = Type;
	HM = h;
	PassengerID = PassID;
	this->StartS = StartS;
	this->EndS = ES;
	this->PsType = PsType;
}


void Event::setEventID(int ID)
{
	this->EventID = ID;
}
int Event::getEventID() const
{
	return this->EventID;
}

void Event::setEventType(bool Type)
{
	this->EventType = Type;
}
bool Event::getEventType() const
{
	return this->EventType;
}

void Event::setHM(TimeHM h)
{
	HM = h;
}
TimeHM Event::getHM() const
{
	return this->HM;
}

void Event::setPassengerID(int PassID)
{
	PassengerID = PassID;
}
int Event::getPassengerID() const
{
	return PassengerID;
}

void Event::setStartS(int Start)
{
	StartS = Start;
}
int Event::getStartS() const
{
	return StartS;
}

void Event::setEndS(int E)
{
	this->EndS = E;
}
int Event::getEndS() const
{
	return this->EndS;
}

void Event::setPsType(int PsType)
{
	this->PsType = PsType;
}
int Event::getPsType() const
{
	return this->PsType;
}

Event::~Event()
{

}
