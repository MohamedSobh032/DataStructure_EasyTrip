#include "DEFS.h"
#include "TimeHM.h"
#include "Bus.h"

Bus::Bus()
{
	this->BusID = 0;
	this->BusType = MB;
	this->BusStatus = Working;
	this->MaintenanceTime = 0;
	this->CurrentPassenger = 0;
	this->CurrentStation = -1;
	this->JourneysTaken = 0;
	this->Direction = FWD;
	this->TotalPassengers = 0;
	this->TotalJourneysTaken = 0;
}
Bus::Bus(int Id, bool T, int MT)
{
	this->BusID = Id;
	this->BusType = T;
	this->BusStatus = Working;
	this->MaintenanceTime = MT;
	this->CurrentPassenger = 0;
	this->CurrentStation = -1;
	this->JourneysTaken = 0;
	this->Direction = FWD;
	this->TotalPassengers = 0;
	this->TotalJourneysTaken = 0;
}

void Bus::setBusID(int ID)
{
	this->BusID = ID;
}
int Bus::getBusID() const
{
	return this->BusID;
}

void Bus::setBusType(bool T)
{
	this->BusType = T;
}
bool Bus::getBusType() const
{
	return this->BusType;
}

void Bus::setBusStatus(bool S)
{
	this->BusStatus = S;
}
bool Bus::getBusStatus() const
{
	return this->BusStatus;
}
void Bus::ToggleBusStatus()
{
	if (this->BusStatus == Working)
	{
		this->BusStatus = Maintenance;
	}
	else
	{
		this->BusStatus = Working;
	}
}

void Bus::setMaintenanceTime(int MT)
{
	this->MaintenanceTime.setMinutes(MT);
}
TimeHM Bus::getMaintenanceTime() const
{
	return this->MaintenanceTime;
}
bool Bus::DecrementMaintenanceTime(int TimeStepInSeconds)
{
	this->MaintenanceTime -= TimeStepInSeconds;
	if (this->MaintenanceTime <= 0)
	{
		this->ToggleBusStatus();
		return true;
	}
	return false;
}

void Bus::setCurrentPassenger(int CP)
{
	this->CurrentPassenger = CP;
}
int Bus::getCurrentPassenger() const
{
	return this->CurrentPassenger;
}
int Bus::getAvailablePassenger(int C)
{
	return (C - this->CurrentPassenger);
}

bool Bus::AddPassenger(int C, Passenger*& p)
{
	if (this->getAvailablePassenger(C) <= 0)
		return false;
	else
	{
		if (this->Direction == FWD)
			this->PassengerOnBus.enqueue(p->getEndStation(), p);
		else
			this->PassengerOnBus.enqueue(-1*p->getEndStation(), p);
		this->TotalPassengers++;
		this->CurrentPassenger++;
		return true;
	}
}
bool Bus::DropPassenger(Passenger*& ps)
{
	if (PassengerOnBus.isEmpty())
		return true;
	int prio = 0;
	PassengerOnBus.peek(prio,ps);

	if (Direction == FWD && prio == CurrentStation)
	{
		PassengerOnBus.dequeue(prio, ps);
		this->CurrentPassenger--;
	}
	else if (Direction == BWD && -1 * prio == CurrentStation)
	{
		PassengerOnBus.dequeue(prio, ps);
		this->CurrentPassenger--;
	}
	else if (Direction == FWD && prio != CurrentStation)
		ps = nullptr;
	else if (Direction == BWD && -1 * prio != CurrentStation)
		ps = nullptr;
	return true;
}

void Bus::setTotalPassengers(int TP)
{
	this->TotalPassengers = TP;
}
int Bus::getTotalPassengers() const
{
	return this->TotalPassengers;
}
void Bus::IncrementTotalPassengers()
{
	this->TotalPassengers++;
}

void Bus::setCurrentStation(int CS)
{
	this->CurrentStation = CS;
}
void Bus::IncrementCurrentStation()
{
	if (Direction == FWD)
		this->CurrentStation++;
	else
		this->CurrentStation--;
}
int Bus::getCurrentStation() const
{
	return this->CurrentStation;
}

void Bus::setJourneysTaken(int JT)
{
	this->JourneysTaken = JT;
}
int Bus::getJourneysTaken() const
{
	return this->JourneysTaken;
}
bool Bus::IncrementJourneysTaken(int MAXJ, int WBMT, int MBMT)
{
	this->JourneysTaken++;
	if (this->JourneysTaken >= MAXJ)
	{
		if (this->CurrentStation == 0)
		{
			this->BusStatus = Maintenance;
			this->JourneysTaken = 0;
			if (this->BusType == MB)
				this->setMaintenanceTime(MBMT);
			else
				this->setMaintenanceTime(WBMT);
			return true;
		}
	}
	return false;
}

void Bus::setDirection(bool D)
{
	this->Direction = D;
}
bool Bus::getDirection() const
{
	return this->Direction;
}
void Bus::ToggleDirection()
{
	if (this->Direction == BWD)
		this->Direction = FWD;
	else
		this->Direction = BWD;
}

void Bus::setTotalJourneysTaken(int TJ)
{
	this->TotalJourneysTaken = TJ;
}
int Bus::getTotalJourneysTaken() const
{
	return this->TotalJourneysTaken;
}
void Bus::IncrementTotalJourneysTaken()
{
	this->TotalJourneysTaken++;
}

void Bus::setTimeNotInStation(TimeHM t)
{
	this->TimeNotInStation = t;
}
TimeHM Bus::getTimeNotInStation() const
{
	return this->TimeNotInStation;
}
bool Bus::IncrementTimeNotInStation(int TimeBetweenStationInMinutes, int StepSizeInSeconds)
{
	this->TimeNotInStation += StepSizeInSeconds;
	if (!PassengerOnBus.isEmpty())
	{
		this->BusyTime += StepSizeInSeconds;
	}

	if (this->TimeNotInStation.getMinutes() >= TimeBetweenStationInMinutes)
	{
		this->TimeNotInStation = 0;
		return true;
	}
	return false;
}
void Bus::ResetTimeNotInStation()
{
	this->TimeNotInStation = 0;
}

void Bus::setTotalTimeInStation(TimeHM t)
{
	this->TotalTimeInStation = t;
}
TimeHM Bus::getTotalTimeInStation() const
{
	return this->TotalTimeInStation;
}
bool Bus::IncrementTotalTimeInStation(int StepSizeInSeconds, int StationID)
{

	if (!PassengerOnBus.isEmpty())
	{
		this->BusyTime += StepSizeInSeconds;
	}

	if (StationID == 0)
		return false;
	else
		this->TotalTimeInStation += StepSizeInSeconds;
	return true;
}

void Bus::setBusyTime(TimeHM t)
{
	this->BusyTime = t;
}
TimeHM Bus::getBusyTime() const
{
	return this->BusyTime;
}
void Bus::IncrementBusyTime(int StepSizeInSeconds)
{
	if (!this->PassengerOnBus.isEmpty())
		this->BusyTime += StepSizeInSeconds;
}

float Bus::BusUtilization(int BCM, int BCW, TimeHM TS)
{
	float busu;
	int STS = TS.getHours() * 3600 + TS.getMinutes() * 60 + TS.getSeconds();
	int SBT = this->BusyTime.getHours() * 3600 + this->BusyTime.getMinutes() * 60 + this->BusyTime.getSeconds();

	if (this->TotalJourneysTaken == 0)
		return 0;
	if (STS == 0)
		return 0;

	if (this->BusType == MB)
		busu = (float)(this->TotalPassengers) / (float)(BCM * this->TotalJourneysTaken) * (float)(SBT / STS);
	else
		busu = (float)(this->TotalPassengers) / (float)(BCW * this->TotalJourneysTaken) * (float)(SBT / STS);
	return busu;
}




bool Bus::getPassenger(int index, int& PID)
{
	int dummyprio = 0;
	return this->PassengerOnBus.PeekSpecific(PID, dummyprio, index);
}

Bus::Bus(const Bus& b)
{
	this->BusID = b.BusID;
	this->BusType = b.BusType;
	this->BusStatus = b.BusStatus;
	this->MaintenanceTime = b.MaintenanceTime;
	this->CurrentPassenger = b.CurrentPassenger;
	this->PassengerOnBus = b.PassengerOnBus;
	this->TotalPassengers = b.TotalPassengers;
	this->CurrentStation = b.CurrentStation;
	this->JourneysTaken = b.JourneysTaken;
	this->Direction = b.Direction;
	this->TotalJourneysTaken = b.TotalJourneysTaken;
	this->TimeNotInStation = b.TimeNotInStation;
	this->TotalTimeInStation = b.TotalTimeInStation;
	this->BusyTime = b.BusyTime;
}

Bus::~Bus()
{

}