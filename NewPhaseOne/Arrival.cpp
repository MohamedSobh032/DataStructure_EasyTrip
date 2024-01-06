#include "DEFS.h"
#include "Arrival.h"
Arrival::Arrival(int EventID, int psType, TimeHM AT, int PassID, int SS, int ES)
{
	this->EventID = EventID;
	this->EventType = Arriv;
	this->HM = AT;
	this->PassengerID = PassID;
	this->StartS = SS;
	this->EndS = ES;
	this->PsType = psType;
}

void Arrival::setEndS(int EndS)
{
	this->EndS = EndS;
}
int Arrival::getEndS() const
{
	return this->EndS;
}

void Arrival::setPsType(int PsType)
{
	this->PsType = PsType;
}
int Arrival::getPsType() const
{
	return this->PsType;
}


bool Arrival::Execute(Passenger* newps, Station* s)
{
	s->AddPassengerToQueue(newps);
	return true;
}

Arrival::~Arrival()
{

}