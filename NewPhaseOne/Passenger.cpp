
#include "DEFS.h"
#include "Passenger.h"


Passenger::Passenger()
{
	this->PassengerID = 0;
	this->StartStation = 0;
	this->EndStation = 0;
	this->PassengerType = NP;
	this->PassengerStatus = waiting;
	this->OnOffTime = 0;
	this->AT = 0;
	this->WT = 0;
}
Passenger::Passenger(int id, int StartS, int EndS, int PassType, TimeHM ArrivalTime, int OFT)
{
	this->PassengerID = id;
	this->StartStation = StartS;
	this->EndStation = EndS;
	this->PassengerType = PassType;
	this->PassengerStatus = waiting;
	this->OnOffTime = OFT;
	AT = ArrivalTime;
	WT = 0;
}

void Passenger::setPassengerID(int id)
{
	this->PassengerID = id;
}
int Passenger::getPassengerID() const
{
	return this->PassengerID;
}

void Passenger::setStartStation(int SS)
{
	this->StartStation = SS;
}
int Passenger::getStartStation() const
{
	return this->StartStation;
}

void Passenger::setEndStation(int ES)
{
	this->EndStation = ES;
}
int Passenger::getEndStation() const
{
	return this->EndStation;
}

void Passenger::setPassengerType(int PT)
{
	this->PassengerType = PT;
}
int Passenger::getPassengerType() const
{
	return this->PassengerType;
}

void Passenger::setPassengerStatus(bool Status)
{
	this->PassengerStatus = Status;
}
bool Passenger::getPassengerStatus() const
{
	return this->PassengerStatus;
}

void Passenger::setPromoted()
{
	this->PassengerType = PNP;
}
bool Passenger::getPromoted() const
{
	return (this->PassengerType == PNP);
}

void Passenger::setOnOffTime(int OnOffTime)
{
	this->OnOffTime = OnOffTime;
}
TimeHM Passenger::getOnOffTime() const
{
	return this->OnOffTime;
}
void Passenger::DecrementOnOffTime(TimeHM t)
{
	this->OnOffTime -= t;
}

void Passenger::setAT(TimeHM At)
{
	this->AT = At;
}
TimeHM Passenger::getAT() const
{
	return AT;
}

void Passenger::setWT(TimeHM Wt)
{
	this->WT = Wt;
}
TimeHM Passenger::getWT() const
{
	return this->WT;
}
bool Passenger::IncrementWT(int TimeStepInSeconds, int maxWT)
{
	WT += TimeStepInSeconds;
	if (WT.getMinutes() >= maxWT && PassengerType == NP)
		return true;
	return false;
}

void Passenger::setFT(TimeHM FT)
{
	this->FT = FT;
}
TimeHM Passenger::getFT() const
{
	return this->FT;
}

Passenger::Passenger(const Passenger& P)
{
	this->PassengerID = P.PassengerID;
	this->StartStation = P.StartStation;
	this->EndStation = P.EndStation;
	this->PassengerType = P.PassengerType;
	this->PassengerStatus = P.PassengerStatus;
	this->OnOffTime = P.OnOffTime;
	this->AT = P.AT;
	this->WT = P.WT;
	this->FT = P.FT;
}

Passenger::~Passenger()
{

}